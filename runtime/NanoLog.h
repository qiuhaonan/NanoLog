#ifndef NANOLOG_H
#define NANOLOG_H

/**
 * This header serves as the application and generated code interface into
 * the NanoLog Runtime system. This should be included where-ever the NANO_LOG
 * macro is used.
 */

namespace NanoLog {

// This extra namespace allows users to import only the LogLevel namespace
// via the "using" directive (Ex: using namespace NanoLogLevels;)
namespace LogLevels {
    /**
     * The levels of verbosity for messages logged with #NANO_LOG.
     */
    enum LogLevel {
        // Keep this in sync with logLevelNames defined inside Log.cc.
                SILENT_LOG_LEVEL = 0,
        /**
         * Bad stuff that shouldn't happen. The system broke its contract to
         * users in some way or some major assumption was violated.
         */
                ERROR,
        /**
         * Messages at the WARNING level indicate that, although something went
         * wrong or something unexpected happened, it was transient and
         * recoverable.
         */
                WARNING,
        /**
         * Somewhere in between WARNING and DEBUG...
         */
                NOTICE,
        /**
         * Messages at the DEBUG level don't necessarily indicate that anything
         * went wrong, but they could be useful in diagnosing problems.
         */
                DEBUG,
        NUM_LOG_LEVELS // must be the last element in the enum
    };
};
using namespace LogLevels;

// User API

/**
 * Preallocate the thread-local data structures needed by the
 * NanoLog system for the current thread. Although optional, it is
 * recommended to invoke this function in every thread that will use the
 * NanoLog system before the first log message.
 */
void preallocate();

/**
 * Sets the file location for the NanoLog output. All NANO_LOG statements
 * invoked after this function returns are guaranteed to be in the new file
 * location.
 *
 * \param filename
 *      Where to place the log file
 */
void setLogFile(const char* filename);

/**
 * Sets the minimum logging severity level in the system. All log statements
 * of a lower log severity will be dropped completely.
 *
 * \param logLevel
 *      New Log level to set
 */
void setLogLevel(LogLevel logLevel);

/**
 * Returns the current minimum log severity level enforced by NanoLog
 */
LogLevel getLogLevel();

/**
 * Waits until all pending log statements are persisted to disk. Note that if
 * there is another logging thread continually adding new pending log
 * statements, this function may not return until all threads stop logging and
 * all the new log statements are also persisted.
 */
void sync();

// Debugging API

/**
 * Print various statistics gathered by the NanoLog system to stdout. This
 * is primarily intended as a performance debugging aid and the reported
 * performance metrics may not be 100% consistent since they are read without
 * synchronization.
 */
void printStats();

/**
 * Prints the configuration parameters being used by NanoLog to stdout. This is
 * primarily used to keep track of configurations for benchmarking.
 */
void printConfig();

}; // namespace NanoLog


// These header files are needed for the in-lined runtime code. They are
// included here so that the user of the NanoLog system only has to
// #include one file.
#include <cstring>         /* strlen + memcpy */
#include "RuntimeLogger.h"

#endif // NANOLOG_H
