/* 
 * File:   Main.c
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 11:20
 */

#include <gtest/gtest.h>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>



using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


int main(int argc, char** argv) {
    DOMConfigurator::configure("Log4cxxConfig.xml");
    LogString strAppenderName = "appxConsoleAppender";
    LoggerPtr root = Logger::getRootLogger();
    root->removeAppender(strAppenderName);	
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

