#ifndef __dbg_h__
#define __dbg_h__

/* Adapted from Zed Shaw's awesome debug macros */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifdef NDEBUG
#define debug(...)
#else
#define debug(...) do { fprintf(stderr, "[DEBUG] (%s:%d) ", __FILE__, __LINE__);\
                   fprintf(stderr, __VA_ARGS__); \
                   fprintf(stderr, "\n"); } while (0)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(...) do { fprintf(stderr, "[ERROR] (%s:%d: errno: %s) ", __FILE__, __LINE__, clean_errno()); \
                     fprintf(stderr, __VA_ARGS__); \
                     fprintf(stderr, "\n"); } while (0)

#define log_warn(...) do { fprintf(stderr, "[WARN] (%s:%d: errno: %s) ", __FILE__, __LINE__, clean_errno()); \
                      fprintf(stderr, __VA_ARGS__); \
                      fprintf(stderr, "\n"); } while (0)

#define log_info(...) do { fprintf(stderr, "[INFO] (%s:%d) ", __FILE__, __LINE__);\
                      fprintf(stderr, __VA_ARGS__); \
                      fprintf(stderr, "\n"); } while (0)

#define check(A, ...) if(!(A)) { log_err(__VA_ARGS__); errno=0; goto error; }
#define check_warn(A, ...) if(!(A)) { log_warn(__VA_ARGS__);}

#define sentinel(...) { log_err(__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_null(A) check((A), "Got null pointer for %s\n", #A)

#define check_debug(A, ...) if (!(A)) { debug(__VA_ARGS__); errno=0; goto error; }


#ifdef PROFILE
#define tu_get_time(__t) __t = omp_get_wtime()
#define tu_log_runtime(__start, __end, ...) do { \
        fprintf(stdout, __VA_ARGS__); \
        fprintf(stdout, "%lf sec\n", __end - __start); \
} while (0)

#else

#define tu_get_time(__t)
#define tu_log_runtime(__start, __end, ...)

#endif // define PROFILE


static inline int get_env_num_threads()
{
        char * num_threads_as_str = getenv("OMP_NUM_THREADS");
        long num_threads;
        if (num_threads_as_str != NULL) {
                num_threads = atoi(num_threads_as_str);
        } else {
                num_threads = 0;
        }

        return num_threads;
}


#endif /* Inclusion guard */
