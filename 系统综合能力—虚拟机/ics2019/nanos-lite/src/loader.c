#include "proc.h"
#include <elf.h>
#include <fs.h>

#ifdef __ISA_AM_NATIVE__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

size_t ramdisk_read(void *buf, size_t offset, size_t len);


//finished loader
static uintptr_t loader(PCB *pcb, const char *filename) {
  Elf_Ehdr head;
  int fd=fs_open(filename,0,0);
  fs_lseek(fd,0,SEEK_SET);
  fs_read(fd,&head,sizeof(head));
  for(int i=0;i<head.e_phnum;i++){
    Elf_Phdr temp;
    fs_lseek(fd,head.e_phoff+i*head.e_phentsize,SEEK_SET);
    fs_read(fd,&temp,sizeof(temp));
    if(temp.p_type==PT_LOAD){
      fs_lseek(fd,temp.p_offset,SEEK_SET);
      fs_read(fd,(void*)temp.p_vaddr,temp.p_filesz);
      memset((void*)(temp.p_vaddr+temp.p_filesz),0,temp.p_memsz-temp.p_filesz);
    }
  }
  return head.e_entry;
}

//finished naive_uload
void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %x", entry);
  ((void(*)())entry) ();
}

void context_kload(PCB *pcb, void *entry) {
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
