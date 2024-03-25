#pragma once

#ifdef BKM_STRING
    #include <bakatools/string/string_tools.h>
#endif
#ifdef BKM_BASE
    #include <bakatools/logging/log.h> 
    #include <bakatools/logging/assert.h>
#endif
#ifdef BKM_TIME_AND_THREADS
    #include <bakatools/time/time.h>
    #include <bakatools/thread/task_timer.h>
#endif
#ifdef BKM_FILESYSTEM
    #include <bakatools/file_system/file_watcher.h>
#endif
#ifdef BKM_DATASTRUCT
    #include <bakatools/data_struct/trie.h>
#endif