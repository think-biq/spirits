# spirits

Accounting library, to keep track of (virtual) storage / memory usage.

## Examples

```c
spirits_t s;

// Create 1kb of memory to keep track of.
if (0 != spirits_summon(&s, 1024)) {
	printf("Could not summon spiris.\n");
	return 13;
}

uint64_t address = 0;
// Allocate memory and return address as relative offset to the start of the
// virtual memory space.
if (0 == spirits_allocate(&s, &address, 64)) {
	printf("Allocated %u bytes at offset: %llu\n", 64, address);
}
else {
	printf("Allocation error :/\n");
	return -1;
}

// Free any memory allocated at given address.
spirits_free(&s, address);

// Clear virtual memory.
spirits_banish(&s);

```