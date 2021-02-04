# 操作系统调用封装

## ！！系统调用API还在设计中！！

完整的newlib需要以下系统调用的实现(待补充)：

```
int _open(const char *path, int flags, mode_t mode);
int _read(int fd, void *buf, size_t count);
int _write(int fd, const void *buf, size_t count);
void _exit(int status);
int _kill(int pid, int sig);
pid_t _getpid();
int _close(int fd);
off_t _lseek(int fd, off_t offset, int whence);
void *_sbrk(intptr_t increment);
int _fstat(int fd, struct stat *buf);
time_t time(time_t *tloc);
int signal(int num, void *handler);
int _execve(const char *fname, char * const argv[], char *const envp[]);
pid_t _fork();
int _link(const char *d, const char *n);
int _unlink(const char *n);
pid_t _wait(int *status);
clock_t _times(void *buf);
int _gettimeofday(struct timeval *tv);
```

这些系统调用是平台相关的，libos包含实现这些系统调用的代码。对于不是POSIX兼容的系统(如自制迷你操作系统)，一些系统调用可以模拟实现，一些可以留空(返回失败或assert fail)。