#ifndef __X86_H__
#define __X86_H__

// CPU rings
#define DPL_KERN       0x0     // Kernel (ring 0)
#define DPL_USER       0x3     // User (ring 3)

// Application segment type bits
#define STA_X          0x8     // Executable segment
#define STA_W          0x2     // Writeable (non-executable segments)
#define STA_R          0x2     // Readable (executable segments)

// System segment type bits
#define STS_T32A       0x9     // Available 32-bit TSS
#define STS_IG32       0xE     // 32-bit Interrupt Gate
#define STS_TG32       0xF     // 32-bit Trap Gate

// Eflags register
#define FL_TF          0x00000100  // Trap Flag
#define FL_IF          0x00000200  // Interrupt Enable

// Control Register flags
#define CR0_PE         0x00000001  // Protection Enable
#define CR0_PG         0x80000000  // Paging

// Page directory and page table constants
#define PGSIZE         4096    // Bytes mapped by a page
#define PGMASK         4095    // Mask for bit ops
#define NR_PDE         1024    // # directory entries per page directory
#define NR_PTE         1024    // # PTEs per page table
#define PGSHFT         12      // log2(PGSIZE)
#define PTXSHFT        12      // Offset of PTX in a linear address
#define PDXSHFT        22      // Offset of PDX in a linear address

// Page table/directory entry flags
#define PTE_P          0x001   // Present
#define PTE_W          0x002   // Writeable
#define PTE_U          0x004   // User
#define PTE_PWT        0x008   // Write-Through
#define PTE_PCD        0x010   // Cache-Disable
#define PTE_A          0x020   // Accessed
#define PTE_D          0x040   // Dirty

// GDT entries
#define NR_SEG         6       // GDT size
#define SEG_KCODE      1       // Kernel code
#define SEG_KDATA      2       // Kernel data/stack
#define SEG_UCODE      3       // User code
#define SEG_UDATA      4       // User data/stack
#define SEG_TSS        5       // Global unique task state segement
#define KSEL(desc)     (((desc) << 3) | DPL_KERN)
#define USEL(desc)     (((desc) << 3) | DPL_USER)

// IDT size
#define NR_IRQ         256     // IDT size

// Interrupts and exceptions
#define T_IRQ0         32
#define IRQ_TIMER      0
#define IRQ_KBD        1
#define IRQ_ERROR      19
#define IRQ_SPURIOUS   31
#define EX_DIV         0
#define EX_UD          6
#define EX_NM          7
#define EX_DF          8
#define EX_TS          10
#define EX_NP          11
#define EX_SS          12
#define EX_GP          13
#define EX_PF          14
#define EX_MF          15
#define EX_SYSCALL     0x80

#define IRQS(_) \
  _(  0, KERN, NOERR) _(  1, KERN, NOERR) \
  _(  2, KERN, NOERR) _(  3, KERN, NOERR) \
  _(  4, KERN, NOERR) _(  5, KERN, NOERR) \
  _(  6, KERN, NOERR) _(  7, KERN, NOERR) \
  _(  8, KERN,   ERR) _(  9, KERN, NOERR) \
  _( 10, KERN,   ERR) _( 11, KERN,   ERR) \
  _( 12, KERN,   ERR) _( 13, KERN,   ERR) \
  _( 14, KERN,   ERR) _( 15, KERN, NOERR) \
  _( 16, KERN, NOERR) _( 19, KERN, NOERR) \
  _( 31, KERN, NOERR) \
  _( 32, KERN, NOERR) _( 33, KERN, NOERR) \
  _( 34, KERN, NOERR) _( 35, KERN, NOERR) \
  _( 36, KERN, NOERR) _( 37, KERN, NOERR) \
  _( 38, KERN, NOERR) _( 39, KERN, NOERR) \
  _( 40, KERN, NOERR) _( 41, KERN, NOERR) \
  _( 42, KERN, NOERR) _( 43, KERN, NOERR) \
  _( 44, KERN, NOERR) _( 45, KERN, NOERR) \
  _( 46, KERN, NOERR) _( 47, KERN, NOERR) \
  _(128, USER, NOERR)

// Below are only defined for c/cpp files
#ifndef __ASSEMBLER__

// +--------10------+-------10-------+---------12----------+
// | Page Directory |   Page Table   | Offset within Page  |
// |      Index     |      Index     |                     |
// +----------------+----------------+---------------------+
//  \--- PDX(va) --/ \--- PTX(va) --/\------ OFF(va) ------/
typedef uint32_t PTE;
typedef uint32_t PDE;
#define PDX(va)          (((uint32_t)(va) >> PDXSHFT) & 0x3ff)
#define PTX(va)          (((uint32_t)(va) >> PTXSHFT) & 0x3ff)
#define OFF(va)          ((uint32_t)(va) & 0xfff)
#define ROUNDUP(a, sz)   ((((uintptr_t)a)+(sz)-1) & ~((sz)-1))
#define ROUNDDOWN(a, sz) ((((uintptr_t)a)) & ~((sz)-1))
#define PTE_ADDR(pte)    ((uint32_t)(pte) & ~0xfff)
#define PGADDR(d, t, o)  ((uint32_t)((d) << PDXSHFT | (t) << PTXSHFT | (o)))

// Segment Descriptor
typedef struct SegDesc {
  uint32_t lim_15_0 : 16;  // Low bits of segment limit
  uint32_t base_15_0 : 16; // Low bits of segment base address
  uint32_t base_23_16 : 8; // Middle bits of segment base address
  uint32_t type : 4  ;     // Segment type (see STS_ constants)
  uint32_t s : 1;          // 0 = system, 1 = application
  uint32_t dpl : 2;        // Descriptor Privilege Level
  uint32_t p : 1;          // Present
  uint32_t lim_19_16 : 4;  // High bits of segment limit
  uint32_t avl : 1;        // Unused (available for software use)
  uint32_t rsv1 : 1;       // Reserved
  uint32_t db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
  uint32_t g : 1;          // Granularity: limit scaled by 4K when set
  uint32_t base_31_24 : 8; // High bits of segment base address
} SegDesc;

#define SEG(type, base, lim, dpl) (SegDesc)             \
{  ((lim) >> 12) & 0xffff, (uint32_t)(base) & 0xffff,   \
  ((uint32_t)(base) >> 16) & 0xff, type, 1, dpl, 1,     \
  (uint32_t)(lim) >> 28, 0, 0, 1, 1, (uint32_t)(base) >> 24 }

#define SEG16(type, base, lim, dpl) (SegDesc)           \
{  (lim) & 0xffff, (uint32_t)(base) & 0xffff,           \
  ((uint32_t)(base) >> 16) & 0xff, type, 0, dpl, 1,     \
  (uint32_t)(lim) >> 16, 0, 0, 1, 0, (uint32_t)(base) >> 24 }

// Gate descriptors for interrupts and traps
typedef struct GateDesc {
  uint32_t off_15_0 : 16;   // Low 16 bits of offset in segment
  uint32_t cs : 16;         // Code segment selector
  uint32_t args : 5;        // # args, 0 for interrupt/trap gates
  uint32_t rsv1 : 3;        // Reserved(should be zero I guess)
  uint32_t type : 4;        // Type(STS_{TG,IG32,TG32})
  uint32_t s : 1;           // Must be 0 (system)
  uint32_t dpl : 2;         // Descriptor(meaning new) privilege level
  uint32_t p : 1;           // Present
  uint32_t off_31_16 : 16;  // High bits of offset in segment
} GateDesc;

#define GATE(type, cs, entry, dpl) (GateDesc)                \
{  (uint32_t)(entry) & 0xffff, (cs), 0, 0, (type), 0, (dpl), \
  1, (uint32_t)(entry) >> 16 }


// Task state segment format
typedef struct TSS {
  uint32_t link;     // Unused
  uint32_t esp0;     // Stack pointers and segment selectors
  uint32_t ss0;      //   after an increase in privilege level
  char     padding[88];
} TSS;

// Interrupt and exception frame
typedef struct TrapFrame {
  uint32_t edi, esi, ebp, esp_;
  uint32_t ebx, edx, ecx, eax;   // Register saved by pushal
  uint32_t es, ds;               // Segment register
  int32_t  irq;                  // # of irq
  uint32_t err, eip, cs, eflags; // Execution state before trap 
  uint32_t esp, ss;              // Used only when returning to DPL=3
} TrapFrame;

// Multiprocesor configuration
typedef struct MPConf {    // configuration table header
  uint8_t  signature[4];    // "PCMP"
  uint16_t length;         // total table length
  uint8_t  version;         // [14]
  uint8_t  checksum;        // all bytes must add up to 0
  uint8_t  product[20];     // product id
  uint32_t *oemtable;      // OEM table pointer
  uint16_t oemlength;      // OEM table length
  uint16_t entry;          // entry count
  uint32_t *lapicaddr;     // address of local APIC
  uint16_t xlength;        // extended table length
  uint8_t  xchecksum;       // extended table checksum
  uint8_t  reserved;
} MPConf;

typedef struct MPDesc {
  int     magic;
  MPConf  *conf;     // MP config table addr
  uint8_t length;   // 1
  uint8_t specrev;  // [14]
  uint8_t checksum; // all bytes add to 0
  uint8_t type;     // config type
  uint8_t imcrp;
  uint8_t reserved[3];
} MPDesc;

#define asm  __asm__

static inline uint8_t inb(int port) {
  uint8_t data;
  asm volatile ("inb %1, %0" : "=a"(data) : "d"((uint16_t)port));
  return data;
}

static inline uint16_t inw(int port) {
  uint16_t data;
  asm volatile ("inw %1, %0" : "=a"(data) : "d"((uint16_t)port));
  return data;
}

static inline uint32_t inl(int port) {
  uint32_t data;
  asm volatile ("inl %1, %0" : "=a"(data) : "d"((uint16_t)port));
  return data;
}

static inline void outb(int port, uint8_t data) {
  asm volatile ("outb %%al, %%dx" : : "a"(data), "d"((uint16_t)port));
}

static inline void outw(int port, uint16_t data) {
  asm volatile ("outw %%ax, %%dx" : : "a"(data), "d"((uint16_t)port));
}

static inline void outl(int port, uint32_t data) {
  asm volatile ("outl %%eax, %%dx" : : "a"(data), "d"((uint16_t)port));
}

static inline void cli() {
  asm volatile ("cli");
}

static inline void sti() {
  asm volatile ("sti");
}

static inline void hlt() {
  asm volatile ("hlt");
}

static inline void pause() {
  asm volatile ("pause");
}

static inline uint32_t get_efl() {
  volatile uint32_t efl;
  asm volatile ("pushf; pop %0": "=r"(efl));
  return efl;
}

static inline uint32_t get_cr0(void) {
  volatile uint32_t val;
  asm volatile ("movl %%cr0, %0" : "=r"(val));
  return val;
}

static inline void set_cr0(uint32_t cr0) {
  asm volatile ("movl %0, %%cr0" : : "r"(cr0));
}


static inline void set_idt(GateDesc *idt, int size) {
  volatile static uint16_t data[3];
  data[0] = size - 1;
  data[1] = (uint32_t)idt;
  data[2] = (uint32_t)idt >> 16;
  asm volatile ("lidt (%0)" : : "r"(data));
}

static inline void set_gdt(SegDesc *gdt, int size) {
  volatile static uint16_t data[3];
  data[0] = size - 1;
  data[1] = (uint32_t)gdt;
  data[2] = (uint32_t)gdt >> 16;
  asm volatile ("lgdt (%0)" : : "r"(data));
}

static inline void set_tr(int selector) {
  asm volatile ("ltr %0" : : "r"((uint16_t)selector));
}

static inline uint32_t get_cr2() {
  volatile uint32_t val;
  asm volatile ("movl %%cr2, %0" : "=r"(val));
  return val;
}

static inline void set_cr3(void *pdir) {
  asm volatile ("movl %0, %%cr3" : : "r"(pdir));
}

#endif

#endif
