void sweep() // type 1 
{
 	size_t* curChunk = heap_mem.start-1;
	//curChunk = next_chunk(curChunk);
	while(curChunk < (size_t*) sbrk(0))
	{
		if(!curChunk) return;
		if(is_marked(curChunk))
		{
			clear_mark(curChunk);			
			curChunk = next_chunk(curChunk);
		}
		else if(in_use(curChunk))
		{
			size_t* next = next_chunk(curChunk);
			free(curChunk + 1);
			curChunk = next;
		}
		else curChunk = next_chunk(curChunk);
	}
}



size_t * is_pointer(size_t * ptr) {
   	
   	if(ptr == NULL) return NULL;
	if(ptr < heap_mem.start-1 || ptr > heap_mem.end ) return NULL;
	
	size_t * tChunk = heap_mem.start -1;

	while(tChunk < (size_t*) sbrk(0))
	{
		size_t * tNextChunk = next_chunk(tChunk);
		if(tChunk <= ptr && ptr < tNextChunk) return tChunk;
		tChunk = tNextChunk;
	}
	return NULL;
}


void recMarker(size_t* head)
{	
	size_t* ptr = is_pointer((size_t*)*head);
	if(ptr == NULL) return;
	if(is_marked(ptr)) return;
	mark(ptr);

	size_t* nChunk = next_chunk(ptr);
	size_t* inPtr = ptr +1;
	while(inPtr < nChunk)
	{
		recMarker(inPtr);
		inPtr++;
	}
}



void walk_region_and_mark(void* start, void* end) 
{
	size_t* curMem = (size_t*) start;

	while(curMem < (size_t*) end)
	{
		recMarker(curMem);
		curMem++;
	}
}
