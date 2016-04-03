//
//	memory.h
//
//	Definitions for dealing with memory.
//
//
//	$Id: memory.h,v 1.1 2000/09/20 01:50:19 elm Exp elm $

#ifndef	_memory_h_
#define	_memory_h_

// We can read this address in I/O space to figure out how much memory
// is available on the system.
#define	DLX_MEMSIZE_ADDRESS	0xffff0000

// We currently support 64 KB pages.  This is done as 64 KB pages in
// the level 1 page table and no level 2 page table
// These two constants should be set as follows:
// L1_PAGE_SIZE_BITS -> amount mapped by a single entry in the L1 table
// L2_PAGE_SIZE_BITS -> amount mapped by a single entry in the L2 table
//
// For example, if you have 4KB pages and each L2 page table has 512 entries,
// you'd have 2MB per entry in a L1 table.  That would mean L1_BITS=21 and
// L2_BITS=12.


/*
Page size: 8kb
256 total pages, 2mb total space
Max 512kb virtual space per process
Max 16 physical pages per process
Track using PCB->npages
Allocate 3 pages of test & data, 1 page of user stack when creating a process.
*/

#define	MEMORY_L1_PAGE_SIZE_BITS 13 	// each entry in L1 is 8 KB {default: 16 | 64} //13 Brock //Josh 12
//2^13 = 8192 = 8 KB but L1 + L2 so 2^12 = 4096 so 2^12 [L1] + 2^12 [L2] = 8192
#define	MEMORY_L2_PAGE_SIZE_BITS 13	// if L1 == L2, there's no L2 tables {default: 16}
#define	MEMORY_PAGE_SIZE	(1 << MEMORY_L2_PAGE_SIZE_BITS)

#define	MEMORY_PAGE_MASK	(MEMORY_PAGE_SIZE-1)
#define	MEMORY_MAX_PAGES	0x10000 //16 physical pages * 4 kb per page table = 64 KB //so 64 max entries

#define L1_MAX_ENTRIES 0x100	// max entries in the L1 table - 1 Currently is max entries.. (not 1 less)  //0x100 Brock //
//0x100 = 256
#define TOP_VIRTUAL_ADDRESS_SPACE  L1_MAX_ENTRIES * MEMORY_PAGE_SIZE //Brock: 256 entries * 8kb = 2048 kb{default: 1|64|64}
// 256 entries kind of seems like too much also 2mb is the physical memory space.


// The PTE is valid if this bit is set in the PTE!
#define	MEMORY_PTE_VALID	0x00000001
// The page is dirty if this bit is set in the PTE
#define	MEMORY_PTE_DIRTY	0x00000002
// The page has been referenced if this bit is set in the PTE
#define	MEMORY_PTE_REFERENCED	0x00000004
#define	MEMORY_PTE_MASK		(~(MEMORY_PTE_VALID|MEMORY_PTE_DIRTY|MEMORY_PTE_REFERENCED))

extern int	lastosaddress;		// Defined in an assembly file
extern int	MemoryGetSize ();
extern int	MemoryAllocPage ();
extern void	MemoryFreePage (uint32 page);
extern uint32	MemorySetupPte (uint32 page);
extern void	MemoryFreePte (uint32 pte);
extern uint32	MemoryPteToPage ();
extern void	MemoryModuleInit ();
extern uint32	MemoryTranslateUserToSystem ();
extern int	MemoryCopySystemToUser ();
extern int	MemoryCopyUserToSystem ();

#endif	// _memory_h_
