#ifndef __AMUNIT_H__
#define __AMUNIT_H__

#include <am.h>
#include <klib.h>

#define IOE ({ _ioe_init();  })
#define CTE(h) ({ _Context *h(_Event, _Context *); _cte_init(h); })
#define VME(f1, f2) ({ void *f1(size_t); void f2(void *); _vme_init(f1, f2); })
#define MPE ({ _mpe_init(entry); })

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

extern void (*entry)();

#define CASE(id, entry_, ...) \
  case id: { \
    void entry_(); \
    entry = entry_; \
    __VA_ARGS__; \
    entry_(); \
    break; \
  }

#endif