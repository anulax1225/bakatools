#pragma once

#ifdef BKMOD_ALL
    #define BKMOD_BASE
    #define BKMOD_JSON
    #define BKMOD_STRING
    #define BKMOD_CONTAINER
    #define BKMOD_THREAD
    #define BKMOD_FILESYSTEM
#endif
#ifdef BKMOD_BASE
    #include <bakatools/logging/log.h> 
    #include <bakatools/logging/assert.h>
#endif
#ifdef BKMOD_JSON
    #include <bakatools/json/json_parser.h>
    #include <bakatools/json/json_lexer.h>
    #include <bakatools/json/json_node.h>
#endif
#ifdef BKMOD_STRING
    #include <bakatools/string/string_tools.h>
#endif
#ifdef BKMOD_CONTAINER
    #include <bakatools/container/data_stream.h>
    #include <bakatools/container/trie.h>
#endif
#ifdef BKMOD_THREAD
    #include <bakatools/thread/task_timer.h>
    #include <bakatools/thread/task_delayer.h>
    #define BKMOD_TIME
#endif
#ifdef BKMOD_FILESYSTEM
    #include <bakatools/file_system/dir_entry.h> 
    #include <bakatools/file_system/directory.h>
    #include <bakatools/file_system/file.h>
    #include <bakatools/file_system/file_watcher.h>
    #define BKMOD_TIME
#endif
#ifdef BKMOD_TIME
    #include <bakatools/time/time_span.h>
    #include <bakatools/time/time_point.h>
#endif