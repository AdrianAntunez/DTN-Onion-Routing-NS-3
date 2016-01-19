/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file ui.cpp
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on: 9/1/2016
 */

#include <iostream>
#include <bitset>
#include <exception>
#include <sstream>

#include "core/onion-constants.h"
#include "ui.h"
#include "console-color.h"

const std::map <UserInterface::FlagTypes,UserInterface::OptionInfo>  UserInterface::m_flagNames =
{
   {UserInterface::FlagTypes::FileFlag, {std::string("file"),'f',std::string("Full path to graph file")}},
   {UserInterface::FlagTypes::SourceFlag, {std::string("source"),'s', std::string("Source node for path exploration")}},
   {UserInterface::FlagTypes::DestinationFlag, { std::string("destination"),'d', std::string("Destination node of path exploration")}},
   {UserInterface::FlagTypes::StartTimeFlag, { std::string("startTime"),'i',std::string("Starting time of path exploration")}},
   {UserInterface::FlagTypes::NumPathsFlag, { std::string("numPaths"),'p',std::string("Maximum number of paths to return")}},
   {UserInterface::FlagTypes::NumNodesFlag, { std::string("numNodes"),'n',std::string("Maximum length of explored paths")}},
   {UserInterface::FlagTypes::TransmissionTimeFlag, { std::string("transmissionTime"),'t', std::string("Time spent/required to perform one hop")}},
   {UserInterface::FlagTypes::EndToEndTimeFlag, { std::string("endToEndTime"),'e', std::string("Total time required to traverse path from source to destination")}},
   {UserInterface::FlagTypes::UtilFlag, { std::string("explorationUtil"),'u', std::string("Choose exploration util to use (numeric code): \n\t [0] Oracle Network \n\t [1] TimingBasedAdversary")}},
   {UserInterface::FlagTypes::CyclesFlag, { std::string("disableCycles"),'c', std::string("Disable circular paths (repeated nodes in path)")}},
   {UserInterface::FlagTypes::DynamicFlag, { std::string("dynamicGraph"),'g', std::string("Consider dynamic graph")}},
   {UserInterface::FlagTypes::SizeFlag, { std::string("ofGivenSize"),'o', std::string("Uses numNodes as path length instead of maximum length (only TimingBasedAdversary)")}},
   {UserInterface::FlagTypes::TimeFlag, { std::string("allOfSmallerTime"),'a', std::string("Return all paths smaller than end-to-end time (only TimingBasedAdversary)")}},
};

option UserInterface::m_programOptions[] =
{
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'},
    {m_flagNames.at(UserInterface::FlagTypes::FileFlag).longName.c_str(), required_argument, 0, m_flagNames.at(UserInterface::FlagTypes::FileFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::SourceFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::SourceFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::DestinationFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::DestinationFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::StartTimeFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::StartTimeFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::NumPathsFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::NumPathsFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::NumNodesFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::NumNodesFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::TransmissionTimeFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::TransmissionTimeFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::EndToEndTimeFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::EndToEndTimeFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::UtilFlag).longName.c_str(),  required_argument,  0, m_flagNames.at(UserInterface::FlagTypes::UtilFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::CyclesFlag).longName.c_str(),  no_argument,  0, m_flagNames.at(UserInterface::FlagTypes::CyclesFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::DynamicFlag).longName.c_str(),  no_argument,  0, m_flagNames.at(UserInterface::FlagTypes::DynamicFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::SizeFlag).longName.c_str(),  no_argument,  0, m_flagNames.at(UserInterface::FlagTypes::SizeFlag).shortName},
    {m_flagNames.at(UserInterface::FlagTypes::TimeFlag).longName.c_str(),  no_argument,  0, m_flagNames.at(UserInterface::FlagTypes::TimeFlag).shortName},
    {0, 0, 0, 0}
};


UserInterface::UserInterface():
    m_fileName(""),
    m_sourceId(0),
    m_targetId(0),
    m_startingTime(0),
    m_numPaths(0),
    m_numNodes(0),
    m_transmissionTime(0),
    m_utilIndex(0),
    m_disableCycles(false),
    m_dynamicFlag(false),
    m_givenSize(false),
    m_ofSmallerTime(false)
{

}

UserInterface::UserInterface
    (const std::string &filename,
     const uint32_t &sourceId,
     const uint32_t &destination,
     const uint32_t &startingTime,
     const uint32_t &numPaths,
     const uint32_t &numNodes,
     const uint32_t &transmissionTime,
     const uint32_t &endToEndTime,
     const uint32_t &utilIndex
    ):
    m_fileName(filename),
    m_sourceId(sourceId),
    m_targetId(destination),
    m_startingTime(startingTime),
    m_numPaths(numPaths),
    m_numNodes(numNodes),
    m_transmissionTime(transmissionTime),
    m_endToEndTime(endToEndTime),
    m_utilIndex(utilIndex),
    m_disableCycles(false),
    m_dynamicFlag(false),
    m_givenSize(false),
    m_ofSmallerTime(false)
{

}


UserInterface::~UserInterface()
{

}

bool
UserInterface::getArgs(int argc, char ** argv)
{
    int opt = 0;
    int optIndex = 0;
    uint8_t selOpt = 0;
    opterr = 0;

    std::stringstream ss;
    ss << "OntionPathFinder v." <<  G_VERSION;
    std::cout << ConsoleColor(ConsoleColor::White, ConsoleColor::Bold, ss.str()) << std::string((argc == 1) ? ". Use -h to display program usage." : "") << std::endl;

    ConsoleColor colorText = ConsoleColor(ConsoleColor::Green, ConsoleColor::Bold,"");

    std::ostringstream selectionMsg("",  std::ios_base::app | std::ios_base::out);
    colorText.setText("Provided input values for parameters:");
    selectionMsg << colorText << std::endl;

    std::ostringstream optionFlags("",std::ios_base::app | std::ios_base::out);
    colorText.setColor(ConsoleColor::Blue);
    std::ostringstream optionValue("",std::ios_base::app | std::ios_base::out);

    try {

    while ((opt = getopt_long(argc, argv,"hovacgf:s:d:i:p:n:t:e:u:",
                     m_programOptions, &optIndex )) != -1)
    {
        optionFlags.str("");
        optionValue.str("");
        switch (opt)
        {
                   case 'h' : printUsage();
                       return false;
                   case 'v' : printVersion();
                       return false;
                   case 'a':
                         selOpt = selOpt | FlagTypes::TimeFlag;
                         m_ofSmallerTime = true;
                         optionFlags << "-" << m_flagNames.at(TimeFlag).shortName << " : --" << m_flagNames.at(TimeFlag).longName;
                         optionValue << " = " <<  m_ofSmallerTime << std::endl;
                         break;
                   case 'o':
                        selOpt = selOpt | FlagTypes::SizeFlag;
                        m_givenSize = true;
                        optionFlags << "-" << m_flagNames.at(SizeFlag).shortName << " : --" << m_flagNames.at(SizeFlag).longName;
                        optionValue << " = " <<  m_givenSize << std::endl;
                        break;
                   case 'c' :
                       selOpt = selOpt | FlagTypes::CyclesFlag;
                       m_disableCycles = true;
                       optionFlags << "-" << m_flagNames.at(CyclesFlag).shortName << " : --" << m_flagNames.at(CyclesFlag).longName;
                       optionValue << " = " <<  m_disableCycles << std::endl;
                       break;
                   case 'g':
                       selOpt = selOpt | FlagTypes::DynamicFlag;
                       m_dynamicFlag = true;
                       optionFlags << "-" << m_flagNames.at(DynamicFlag).shortName << " : --" << m_flagNames.at(DynamicFlag).longName;
                       optionValue << " = " <<  m_dynamicFlag << std::endl;
                       break;
                   case 'f' :
                       selOpt = selOpt | FlagTypes::FileFlag;                       
                       m_fileName = std::string(optarg);
                       optionFlags << "-" << m_flagNames.at(FileFlag).shortName << " : --" << m_flagNames.at(FileFlag).longName;
                       optionValue << " = " << m_fileName << std::endl;
                       break;
                   case 's' :
                       selOpt = selOpt | FlagTypes::SourceFlag;
                       m_sourceId = std::stoi(std::string(optarg));
                       optionFlags   << "-" << m_flagNames.at(SourceFlag).shortName << ": --" << m_flagNames.at(SourceFlag).longName;
                       optionValue << " = " << m_sourceId << std::endl;
                       break;
                   case 'd' :
                       selOpt = selOpt | FlagTypes::DestinationFlag;
                       m_targetId = std::stoi(std::string(optarg));
                       optionFlags   << "-" << m_flagNames.at(DestinationFlag).shortName << ": --" << m_flagNames.at(DestinationFlag).longName;
                       optionValue << " = " << m_targetId << std::endl;
                       break;
                   case 'i' :
                       selOpt = selOpt | FlagTypes::StartTimeFlag;
                       m_startingTime = std::stoi(std::string(optarg));
                       optionFlags << "-" << m_flagNames.at(StartTimeFlag).shortName << ": --" << m_flagNames.at(StartTimeFlag).longName;
                       optionValue << " = " << m_startingTime << std::endl;
                       break;
                   case 'p' :
                       selOpt = selOpt | FlagTypes::NumPathsFlag;
                       m_numPaths = std::stoi(std::string(optarg));
                       optionFlags << "-" << m_flagNames.at(NumPathsFlag).shortName << ": --" << m_flagNames.at(NumPathsFlag).longName;
                       optionValue  << " = " << m_numPaths << std::endl;
                       break;
                   case 'n' :
                       selOpt = selOpt | FlagTypes::NumNodesFlag;
                       m_numNodes = std::stoi(std::string(optarg));
                       optionFlags << "-" << m_flagNames.at(NumNodesFlag).shortName << ": --" << m_flagNames.at(NumNodesFlag).longName;
                       optionValue << " = " << m_numNodes << std::endl;
                       break;
                   case 't' :
                       selOpt = selOpt | FlagTypes::TransmissionTimeFlag;
                       m_transmissionTime = std::stoi(std::string(optarg));
                       optionFlags << "-" << m_flagNames.at(TransmissionTimeFlag).shortName << ": --" << m_flagNames.at(TransmissionTimeFlag).longName;
                       optionValue << " = " << m_transmissionTime << std::endl;
                       break;
                   case 'e' :
                       selOpt = selOpt | FlagTypes::EndToEndTimeFlag;
                       m_endToEndTime = std::stoi(std::string(optarg));
                       optionFlags << "-" << m_flagNames.at(EndToEndTimeFlag).shortName << ": --" << m_flagNames.at(EndToEndTimeFlag).longName;
                       optionValue << " = " << m_endToEndTime << std::endl;
                       break;
                   case 'u':
                       selOpt = selOpt | FlagTypes::UtilFlag;
                       m_utilIndex = std::stoi(std::string(optarg));
                       optionFlags << "-" << m_flagNames.at(UtilFlag).shortName << ": --" << m_flagNames.at(UtilFlag).longName;
                       optionValue << " = " << m_utilIndex << std::endl;
                       break;
                   case '?':
                       std::cout << ConsoleColor(ConsoleColor::Red, ConsoleColor::Bold, "Unknown program argument: ") << std::string(1,optopt)
                                 << ConsoleColor(ConsoleColor::Red, ConsoleColor::Bold, " - Use correct parameters and try again.") << std::endl; // Display error and fall down to printUsage()
                   default:
                       printUsage();
                       return false;
        }
        colorText.setText(optionFlags.str());
        selectionMsg << colorText << optionValue.str();
    }

    } catch (std::exception& e) {

        int arg_index = (optind >= 1) ? optind-1 : 0;
        std::stringstream exMsg;
        exMsg << argv[arg_index];
        std::cout << ConsoleColor(ConsoleColor::Red, ConsoleColor::Bold,  "Error occurred while parsing program argument: ")
                  << e.what()
                  << ConsoleColor(ConsoleColor::Red, ConsoleColor::Bold,  " - Wrong value provided for argument: ")
                  << ConsoleColor(ConsoleColor::White, ConsoleColor::Bold,  exMsg.str())
                  << ConsoleColor(ConsoleColor::Red, ConsoleColor::Bold,  " . Use correct parameters and try again.")
                  << std::endl;
        printUsage();
        return false;
    }

    colorText.setText("Default values assumed for unspecified parameters: ");
    colorText.setColor(ConsoleColor::Green);
    std::ostringstream defaultMsg("",  std::ios_base::app | std::ios_base::out);
    defaultMsg << colorText << std::endl;

    for (uint16_t unOpt = 0x01; unOpt <= (0x01 << (m_flagNames.size() -1)); unOpt = unOpt << 1)
    {
        FlagTypes type = static_cast<FlagTypes>(unOpt);
        if (!(selOpt & unOpt))
        {
            defaultMsg << "-"  << ConsoleColor(ConsoleColor::Blue, ConsoleColor::Bold,  std::string(1,m_flagNames.at(type).shortName))
                       << "--" << ConsoleColor(ConsoleColor::Blue, ConsoleColor::Bold,  m_flagNames.at(type).longName)
                       << " = " << getOptionValue(static_cast<FlagTypes>(unOpt)) << std::endl;
        }
    }

    colorText.setColor(ConsoleColor::White);
    colorText.setStyle(ConsoleColor::Bold);
    colorText.setText(std::string(50,'-'));

    std::cout << colorText << std::endl
              << selectionMsg.str()
              << colorText << std::endl
              << defaultMsg.str()
              << colorText << std::endl
              << std::flush;

    return true;

}

void
UserInterface::printUsage() const
{
    std::cout << ConsoleColor(ConsoleColor::Green, ConsoleColor::Bold,"Usage: OntionPathFinder -[hvf:s:d:i:p:n:t:] \nOptions:") << std::endl;

    std::map <FlagTypes,UserInterface::OptionInfo>::const_iterator it;

    for (it = m_flagNames.begin(); it != m_flagNames.end(); ++it)
    {
        std::cout << "-"   << ConsoleColor(ConsoleColor::Blue, ConsoleColor::Bold, std::string(1, it->second.shortName))
                  << " --" << ConsoleColor(ConsoleColor::Blue, ConsoleColor::Bold, it->second.longName)
                  << ": " << it->second.description << std::endl;
    }
}
void
UserInterface::printVersion() const
{
    std::cout << G_VERSION << std::endl;
}

std::string UserInterface::getFileName() const
{
    return m_fileName;
}

uint32_t UserInterface::getUtilIndex() const
{
    return m_utilIndex;
}

uint32_t UserInterface::getSourceId() const
{
    return m_sourceId;
}

uint32_t UserInterface::getStartingTime() const
{
    return m_startingTime;
}

uint32_t UserInterface::getNumPaths() const
{
    return m_numPaths;
}

uint32_t UserInterface::getNumNodes() const
{
    return m_numNodes;
}

uint32_t UserInterface::getTransmissionTime() const
{
    return m_transmissionTime;
}

uint32_t UserInterface::getEndToEndTime() const
{
    return m_endToEndTime;
}

uint32_t UserInterface::getTargetId() const
{
    return m_targetId;
}

bool UserInterface::getDisableCycles() const
{
    return m_disableCycles;
}

bool UserInterface::getDynamicFlag() const
{
    return m_dynamicFlag;
}

bool UserInterface::getGivenSizeFlag() const
{
    return m_givenSize;
}

bool UserInterface::getSmallerTimeFlag() const
{
    return m_ofSmallerTime;
}

std::string UserInterface::getOptionValue(UserInterface::FlagTypes flag)
{
    std::stringstream retval;
    
    switch (flag)
    {
       case TimeFlag: retval << m_ofSmallerTime;
            break;
       case SizeFlag: retval << m_givenSize;
            break;
       case CyclesFlag:  retval << m_disableCycles;
            break;
       case DynamicFlag:  retval << m_dynamicFlag;
            break;
       case FileFlag: retval << m_fileName;
            break;
       case SourceFlag: retval << m_sourceId;
            break;
       case DestinationFlag: retval << m_targetId;
            break;
       case StartTimeFlag: retval << m_startingTime;
            break;
       case NumPathsFlag: retval << m_numPaths;
            break;
       case NumNodesFlag: retval << m_numNodes;
            break;
       case TransmissionTimeFlag: retval << m_transmissionTime;
            break;
       case EndToEndTimeFlag: retval << m_endToEndTime;
            break;
       case UtilFlag:
            switch (m_utilIndex)
            {
                case 0: retval << "Oracle Network"; break;
                case 1: retval << "Timing Adversary"; break;
            }
            break;
       default:
            retval;
    }
    return retval.str();
}







