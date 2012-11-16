package mas.io;

import java.util.ArrayList;
import java.util.List;

public class Chunk {
	protected Chunk(String tag, Chunk parent){
		this.tag = tag;
		this.parentChunk = parent;
		subChunks = new ArrayList<Chunk>();
	}

	protected String tag;
	// start pointer 以tag之前作为开始
	protected long chunkStartPointer;
	// size 包括tag和sub-chunk pointers
	protected long chunkSize;
	protected Chunk parentChunk;
	
	protected List<Chunk> subChunks;
}

class ChunkImpl extends Chunk{

	protected ChunkImpl(String tag, Chunk parent) {
		super(tag, parent);
	}
	
	public void setTag(String tag) {
		this.tag = tag;
	}

	public String getTag() {
		return tag;
	}
	
	public long getChunkStartPointer(){
		return chunkStartPointer;
	}
	
	public void setChunkStartPointer(long value){
		chunkStartPointer = value;
	}
	
	public List<Chunk> getSubChunks(){
		return subChunks;
	}
	
	public ChunkImpl getParent(){
		return (ChunkImpl)parentChunk;
	}
}