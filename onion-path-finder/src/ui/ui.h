/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file ui.h
 * @author Rubén Martínez <rmartinez@deic.uab.cat>
 * @date Created on: 9/1/2016
 */

#ifndef UI_H
#define UI_H
#include <getopt.h>
#include <string>
#include <cstdint>
#include <map>

/**
 * @brief Console based user interface - argument parsing.
 *
 */
class UserInterface
{
public:
    /**
     * @brief Default Constructor
     *
     */
    UserInterface();
    UserInterface(const std::string &filename,
                  const uint32_t &sourceId,
                  const uint32_t &destination,
                  const uint32_t &startingTime,
                  const uint32_t &numPaths,
                  const uint32_t &numNodes,
                  const uint32_t &transmissionTime,
                  const uint32_t &endToEndTime,
                  const uint32_t &utilIndex);
    ~UserInterface();

    /**
     * @brief getArgs: parses command input argument using getopts
     * @return true if all arguments where valid, false otherwhise.
     */
    bool getArgs(int, char *[]);

    /**
     * @brief printUsage: prints correct program usage.
     */
    void printUsage() const;
    /**
     * @brief printVersion: print program version.
     */
    void printVersion() const;


    /**
     * @brief getFileName: get value of option filename
     * @return filename
     */
    std::string getFileName() const;

    /**
     * @brief getUtilIndex: get index of selection util
     * @return utilIndex
     */
    uint32_t getUtilIndex() const;

    /**
     * @brief getSourceId: get value of option source
     * @return source
     */
    uint32_t getSourceId() const;

    /**
     * @brief getStartingTime:  get value of option starting time
     * @return starting time
     */
    uint32_t getStartingTime() const;

    /**
     * @brief getNumPaths: get value of option numPaths
     * @return numPaths
     */
    uint32_t getNumPaths() const;

    /**
     * @brief getNumNodes get value of numNodes
     * @return numNodes
     */
    uint32_t getNumNodes() const;

    /**
     * @brief getTransmissionTime get value of m_transmissionTime
     * @return transmissionTime
     */
    uint32_t getTransmissionTime() const;


    uint32_t getEndToEndTime() const;


    uint32_t getTargetId() const;


    bool getDisableCycles() const;


    bool getDynamicFlag() const;


    bool getGivenSizeFlag() const;


    bool getSmallerTimeFlag() const;


private:

    enum FlagTypes
    {
      FileFlag              = 0x01,
      SourceFlag            = 0x02,
      DestinationFlag       = 0x04,
      StartTimeFlag         = 0x08,
      NumPathsFlag          = 0x10,
      NumNodesFlag          = 0x20,
      TransmissionTimeFlag  = 0x40,
      EndToEndTimeFlag      = 0x80,
      UtilFlag              = 0x100,
      CyclesFlag            = 0x200,
      DynamicFlag           = 0x400,
      SizeFlag              = 0x800,
      TimeFlag              = 0x1000
    };

    struct OptionInfo
    {
      std::string longName;
      char shortName;
      std::string description;
    };

    static const std::map <FlagTypes,OptionInfo> m_flagNames;
    static struct option m_programOptions[];


    std::string m_fileName;
    uint32_t m_sourceId;
    uint32_t m_targetId;
    uint32_t m_startingTime;
    uint32_t m_numPaths;
    uint32_t m_numNodes;
    uint32_t m_transmissionTime;
    uint32_t m_endToEndTime;
    uint32_t m_utilIndex;
    bool m_disableCycles;
    bool m_dynamicFlag;
    bool m_givenSize;
    bool m_ofSmallerTime;

    std::string getOptionValue(FlagTypes flag);

};

#endif // UI_H
