/*Our own header, to be included after  all standard system headers*/
#ifndef __ourhdr_h  
#define __ourhdr_h 
 
#include    <errno.h>               /*for definition of errno                      */
#include    <stdarg.h>              /*ANSI C header file                           */
#include    <sys/types.h>           /* required for some of our prototypes         */  
#include    <stdio.h>               /* for convenience                             */  
#include    <stdlib.h>              /* for convenience                             */  
#include    <string.h>              /* for convenience                             */  
#include    <unistd.h>              /* for convenience                             */ 
  
#define MAXLINE 4096                /* max line length                             */  
#define FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)  
                                        /* default file access permissions for new files */ 
#define DIR_MODE        (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)  
                                        /* default permissions for new directoris */ 
typedef void    Sigfunc(int);   /* for signal handlers */ 
                                        /* 4.3BSD Reno <signal.h> doesn't define  
SIG_ERR */ 
#if     defined(SIG_IGN) && !defined(SIG_ERR)  
#define SIG_ERR ((Sigfunc *)-1)  
#endif  
#define min(a,b)        ((a) < (b) ? (a) : (b))  
#define max(a,b)        ((a) > (b) ? (a) : (b)) 
                                                /* prototypes for our own functions */ 
char    *path_alloc(int *);                     /* {Prog pathalloc} */ 
int      open_max(void);                        /* {Prog openmax} */ 
void     clr_fl(int, int);                      /* {Prog setfl} */ 
void     set_fl(int, int);                      /* {Prog setfl} */ 
void     pr_exit(int);                          /* {Prog prexit} */ 
void     pr_mask(const char *);                 /* {Prog prmask} */ 
Sigfunc *signal_intr(int, Sigfunc *);           /* {Prog signal_intr_function} */ 
int      tty_cbreak(int);                       /* {Prog raw} */ 
int      tty_raw(int);                          /* {Prog raw} */ 
int      tty_reset(int);                        /* {Prog raw} */ 
void     tty_atexit(void);                      /* {Prog raw} */
 
#ifdef  ECHO                                    /* only if <termios.h> has been included */  
struct termios  *tty_termios(void);             /* {Prog raw} */ 
#endif  
void     sleep_us(unsigned int);                /* {Ex sleepus} */ 
ssize_t  readn(int, void *, size_t);            /* {Prog readn} */ 
ssize_t  writen(int, const void *, size_t);     /* {Prog writen} */ 
int              daemon_init(void);                     /* {Prog daemoninit} */ 
int              s_pipe(int *);                         /* {Progs svr4_spipe bsd spipe} */ 
int              recv_fd(int, ssize_t (*func)(int, const void *, size_t));  
                                                        /* {Prog recvfd_svr4 recvfd_43bsd} */
                                                          
int              send_fd(int, int);                     /* {Progs sendfd_svr4 se  
dfd_43bsd} */ 
int              send_err(int, int, const char *);/* {Prog senderr} */ 
int              serv_listen(const char *);     /* {Progs servlisten_svr4 servli  
ten_4  
4bsd} */ 
int              serv_accept(int, uid_t *);     /* {Progs servaccept_svr4 servac  
ept_4  
4bsd} */ 
int              cli_conn(const char *);        /* {Progs cliconn_svr4 cliconn_4  
bsd} */ 
int              buf_args(char *, int (*func)(int, char **));  
                                                /* {Prog bufargs} */ 
int              ptym_open(char *);                     /* {Progs ptyopen_svr4 p yopen_44bsd} */ 
int              ptys_open(int, char *);        /* {Progs ptyopen_svr4 ptyopen_4 bsd} */
  
#ifdef  TIOCGWINSZ  
pid_t    pty_fork(int *, char *, const struct termios *,  
                                  const struct winsize *);      /* {Prog ptyfork */ 
#endif  
int             lock_reg(int, int, int, off_t, int, off_t);     /* {Prog lockreg} */
 
#define read_lock(fd, offset, whence, len)    lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)  
#define readw_lock(fd, offset, whence, len)   lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)  
#define write_lock(fd, offset, whence, len)   lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)  
#define writew_lock(fd, offset, whence, len)  lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)  
#define un_lock(fd, offset, whence, len)      lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)  
pid_t   lock_test(int, int, off_t, int, off_t);      /* {Prog    locktest} */ 
#define is_readlock(fd, offset, whence, len)  lock_test(fd, F_RDLCK, offset, whence, len)  
#define is_writelock(fd, offset, whence, len) lock_test(fd, F_WRLCK, offset, whence, len)  
void    err_dump(const char *, ...);    /* {App misc_source} */ 
void    err_msg(const char *, ...);  
void    err_quit(const char *, ...);  
void    err_ret(const char *, ...);  
void    err_sys(const char *, ...);  
void    log_msg(const char *, ...);             /* {App misc_source} */ 
void    log_open(const char *, int, int);  
void    log_quit(const char *, ...);  
void    log_ret(const char *, ...);  
void    log_sys(const char *, ...);  
void    TELL_WAIT(void);                /* parent/child from {Sec race_condition  } */ 
void    TELL_PARENT(pid_t);  
void    TELL_CHILD(pid_t);  
void    WAIT_PARENT(void);  
void    WAIT_CHILD(void);  
#endif  /* __ourhdr_h */ 
 
static void err_doit(int, const char*, va_list);
char *pname = NULL; /* caller can set this from argv[0]*/
/* Nonfatal error realated to a system call . print a message and return . */
void err_ret(const char *fmt,...)
{
   va_list ap;
   va_start(ap, fmt);
   err_doit(1, fmt, ap);
   va_end(ap);
    
    return;
}
 
/* Fatal error related to a system call . print a message and terminate. */
void err_sys(const char *fmt,...)
{
   va_list ap;
   va_start(ap, fmt);
   err_doit(1, fmt, ap);
   va_end(ap);
   exit(1);
}
/* Fatal error related to a system call . print a message ,dump core ,and terminate. */
void err_dump(const char *fmt,...)
{
   va_list ap;
 
   va_start(ap, fmt);
   err_doit(1, fmt, ap);
   va_end(ap);
   abort(); /* dump core and terminate */
   exit(1); /* shouldn't get here */
}
 
/* Nofatal error related to a system call . print a message and return. */
void err_msg(const char *fmt,...)
{
   va_list ap;
  
   va_start(ap, fmt);
   err_doit(0, fmt, ap);
   va_end(ap);
    
   return;
}
/* Fatal error related to a system call . print a message and terminate. */
void err_quit(const char *fmt,...)
{
   va_list ap;
   va_start(ap, fmt);
   err_doit(0, fmt, ap);
   va_end(ap);
   exit(1);
}
/* print a message and return to caller. caller specifies "errnoflag". */
static void err_doit(int errnoflag, const char *fmt, va_list ap)
{
   int errno_save;
   char buf[MAXLINE];
 
   errno_save = errno;  /* value caller might want printed */
   vsprintf(buf, fmt, ap);
    
   if (errnoflag)
     sprintf(buf+strlen(buf),": %s", strerror(errno_save));
      
   strcat(buf, "\n");
   fflush(stdout); /* in case stdout and stderr are the same */
   fputs(buf, stderr);
   fflush(NULL); /*flushes and stdio  output streams */
    
   return;
}
