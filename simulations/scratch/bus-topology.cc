/*
 * bus-contacts.cc
 *
 *  Created on: April 20, 2015
 *      Author: Adrián Antúnez <adriananve@gmail.com>
 */

#include <iostream>
#include <string>

#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/double.h"
#include "ns3/event-id.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4-interface-container.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/log.h"
#include "ns3/log-macros-disabled.h"
#include "ns3/net-device-container.h"
#include "ns3/node-container.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/nstime.h"
#include "ns3/ptr.h"
#include "ns3/qos-wifi-mac-helper.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/wifi-helper.h"
#include "ns3/wifi-phy-standard.h"
#include "ns3/yans-wifi-helper.h"

NS_LOG_COMPONENT_DEFINE("BusTopology");

using namespace ns3;

class SimulationUtils
{
public:
	SimulationUtils(double interval): progInterval(interval) {}
	void Start(double);

private:
	double progInterval;
	void ProgressNotifier(double, double);
};

void SimulationUtils::Start(double totalTime)
{
	Simulator::Schedule(Seconds(progInterval), &SimulationUtils::ProgressNotifier, this, totalTime, progInterval);
}

void SimulationUtils::ProgressNotifier(double TotalTime, double Interval)
{
	std::clog.precision(4);
	NS_LOG_UNCOND("Simulation Progress: " << ((Simulator::Now ().GetSeconds())*100/TotalTime) << " %");
	Simulator::Schedule(Seconds(Interval), &SimulationUtils::ProgressNotifier, this, TotalTime, Interval);
}

class BusTopology
{
public:
	BusTopology();
	~BusTopology();

	// Configure script parameters
	void Configure(int argc, char **argv);
	void Run();
	void Report();

private:
	uint32_t numNodes;
	double maxRange;
	double interval;
	double endSimulation;
	double progressInterval;
	std::string traceFile;

	void CreateNodes();
	void CreateDevices();
	void InstallInternetStack();
	void InstallApplications();

	NodeContainer nodes;
	Ns2MobilityHelper ns2;
	NetDeviceContainer devices;
	Ipv4InterfaceContainer interfaces;
	//		Ptr<NeighborDiscoveryHelper> daemon;
};

BusTopology::BusTopology() :
	numNodes(1181),			// Nodes
	maxRange(300),			// Meters
	interval(10),			// Seconds
	endSimulation(24),		// Hours
	progressInterval(30),	// Seconds
	traceFile("data/mobility_traces/tue-11-27-traces.ns_movements"),
	ns2(traceFile)
{
}

BusTopology::~BusTopology() {}

void
BusTopology::Configure(int argc, char **argv)
{
//	LogComponentEnable("NeighborDiscoveryHelper", LOG_LEVEL_ALL);
//	LogComponentEnable("MobilityScheduler", LOG_LEVEL_ALL);

	CommandLine cmd;
	cmd.AddValue("maxRange", "Wifi range of each node", maxRange);
	cmd.AddValue("numNodes", "Number of nodes", numNodes);
	cmd.AddValue("interval", "Interval of sth", interval);
	cmd.AddValue ("traceFile", "Ns2 movement trace file", traceFile);
	cmd.Parse(argc, argv);

}

void
BusTopology::Run()
{
	CreateNodes();
	CreateDevices();
	InstallInternetStack();
	InstallApplications();

	double totalTime = endSimulation * 3600;	// Seconds

	std::cout << "Starting simulation for " << totalTime << "s ..." << std::endl;

	SimulationUtils simProgress(progressInterval);
	simProgress.Start(totalTime);

	Simulator::Stop(Seconds(totalTime));
	Simulator::Run();

	std::cout << "Simulation Done!" << std::endl;

	Simulator::Destroy();
}

void
BusTopology::CreateNodes()
{
	std::cout << "Creating " << (unsigned)numNodes << " nodes" << std::endl;

	nodes.Create(numNodes);
	std::cout << "Loading mobility" << std::endl;
	ns2 = Ns2MobilityHelper(traceFile);
	ns2.Install();
}

void
BusTopology::CreateDevices()
{
	std::cout << "Creating and configuring devices" << std::endl;
	std::string phyMode("DsssRate1Mbps");
	// disable fragmentation for frames below 2200 bytes
	Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2000"));
	// turn off RTS/CTS for frames below 500 bytes
	Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("500"));
	// Fix non-unicast data rate to be the same as that of unicast
	Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", StringValue (phyMode));

	WifiHelper wifi;

	YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
	wifiPhy.Set("RxGain", DoubleValue(-10));
	// NS-3 supports RadioTap and Prism tracing extensions for 802.11b
	wifiPhy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO);

	YansWifiChannelHelper wifiChannel;
	wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
	wifiChannel.AddPropagationLoss ("ns3::RangePropagationLossModel","MaxRange", DoubleValue (maxRange));
	wifiPhy.SetChannel (wifiChannel.Create ());


	QosWifiMacHelper wifiMac = QosWifiMacHelper::Default ();
	wifiMac.SetType ("ns3::AdhocWifiMac");

	wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
			"DataMode",StringValue (phyMode),
			"ControlMode",StringValue (phyMode));
	// Set it to adhoc mode
	devices = wifi.Install (wifiPhy, wifiMac, nodes);

	wifiChannel.AddPropagationLoss ("ns3::RangePropagationLossModel","MaxRange", DoubleValue (maxRange));
}

void
BusTopology::InstallInternetStack()
{
	std::cout << "Installing Internet Stack" << std::endl;
	// Set static routing
	Ipv4StaticRoutingHelper staticRouting;

	Ipv4ListRoutingHelper list;
	list.Add (staticRouting, 10);

	InternetStackHelper internet;
	internet.SetRoutingHelper (list); // has effect on the next Install ()

	internet.Install (nodes);

	// Assign IP Addresses
	Ipv4AddressHelper addresses;
	addresses.SetBase ("10.1.0.0", "255.255.0.0");
	interfaces = addresses.Assign (devices);
}

void
BusTopology::InstallApplications()
{
	std::cout << "Installing applications at each node" << std::endl;
	uint16_t port = 4000;
	Time interPacketInterval = Seconds (interval);
	Time nodeExpiration = Seconds(interval*5);

	//	NeighborTopologyMapperHelper mapper(interPacketInterval, port, nodeExpiration);

	// Applications will start when the Aircraft is flying above the ocean
//	for(int i = 0; i < (int) nodes.GetN(); i++)
//	{
		//		ApplicationContainer apps = mapper.Install(nodes.Get(i));
		//		apps.Start(Seconds (0));
		//		apps.Stop(Seconds (endSimulation));
//	}
}


int main(int argc, char **argv)
{

	BusTopology bt = BusTopology();

	bt.Configure(argc, argv);
	bt.Run();

	return 0;
}