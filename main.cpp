#include <iostream>
#include <BasicUsageEnvironment.hh>
#include "testRTSPClient.h"

char eventLoopWatchVariable = 0;

void usage(UsageEnvironment& env, char const* progName) {
    env << "Usage: " << progName << " <rtsp-url-1> ... <rtsp-url-N>\n";
    env << "\t(where each <rtsp-url-i> is a \"rtsp://\" URL)\n";
}

int testRTSPClient(int argc, char** argv) {
    // Begin by setting up our usage environment:
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

    // We need at least one "rtsp://" URL argument:
    if (argc < 2) {
        usage(*env, argv[0]);
        return 1;
    }

    // There are argc-1 URLs: argv[1] through argv[argc-1].  Open and start streaming each one:
    for (int i = 1; i <= argc-1; ++i) {
        openURL(*env, argv[0], argv[i], 6000);
    }

    // All subsequent activity takes place within the event loop:
    env->taskScheduler().doEventLoop(&eventLoopWatchVariable);
    // This function call does not return, unless, at some point in time, "eventLoopWatchVariable" gets set to something non-zero.

    return 0;

    // If you choose to continue the application past this point (i.e., if you comment out the "return 0;" statement above),
    // and if you don't intend to do anything more with the "TaskScheduler" and "UsageEnvironment" objects,
    // then you can also reclaim the (small) memory used by these objects by uncommenting the following code:
    /*
      env->reclaim(); env = NULL;
      delete scheduler; scheduler = NULL;
    */
}

int main(int argc, char** argv)
{
    return testRTSPClient(argc, argv);
}
