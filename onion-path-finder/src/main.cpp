//============================================================================
// Name        : onion-path-finder.cpp
// Author      : Adrian Antunez
// Version     :
// Copyright   : 
// Description : Finds k paths from a given contact table
//============================================================================

#include <iostream>
#include <cstdlib>
#include <memory>
#include <exception>

#include "parsers/parser-factory.h"
#include "parsers/basic-parser.h"
#include "utils/oracle-network.h"
#include "utils/timing-adversary.h"
#include "parsers/id-converter.h"
#include "ui/ui.h"

Nodes nodes;

int main(int argc, char *argv[])
{

    UserInterface ui ( "data/basic/paper-example.txt", 0,0,0,100,100,1,10,1); //Default Configuration Parameters.

    try {
        if (ui.getArgs(argc,argv))
        {
            ParserFactory factory(ui.getFileName());
            std::shared_ptr<Parser> parser = factory.GetParser();
            nodes = parser->Parse(ui.getFileName());

            std::shared_ptr<GraphUtil> util = nullptr;

            switch ( ui.getUtilIndex() )
            {
                case 0:
                    util = std::make_shared<OracleNetwork>(nodes,
                                                           ui.getSourceId(),
                                                           ui.getTargetId(),
                                                           ui.getStartingTime(),
                                                           ui.getNumPaths(),
                                                           ui.getNumNodes(),
                                                           ui.getTransmissionTime(),
                                                           ui.getDisableCycles());
                    break;
                case 1:
                    util = std::make_shared<TimingBasedAdversary>(nodes,
                                                                  ui.getSourceId(),
                                                                  ui.getNumPaths(),
                                                                  ui.getNumNodes(),
                                                                  ui.getTransmissionTime(),
                                                                  ui.getEndToEndTime(),
                                                                  ui.getDisableCycles(),
                                                                  ui.getDynamicFlag(),
                                                                  ui.getGivenSizeFlag(),
                                                                  ui.getSmallerTimeFlag());
                    break;
                default:
                    break;
            }

            PathVector pv = util->getPaths();
            util->printPaths(pv);
        }

    } catch (std::exception& e)  {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
