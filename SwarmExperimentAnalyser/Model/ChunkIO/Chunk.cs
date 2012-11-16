using System;
using System.Collections.Generic;
using System.Text;

namespace SwarmExperimentalAnalyser.Model.ChunkIO {
	public abstract class Chunk {
		abstract public string Tag { get; }
		abstract public bool IsLeaf { get; }
		abstract public List<Chunk> this[string subChunkName] {	get; }
		abstract public List<string> SubchunkTags { get; }
		abstract public byte[] ChunkBytes {	get; }
		/// <summary>
		/// Read Bytes Without Cache From Chunk¡£
		/// </summary>
		/// <param name="offset">Read start position of chunk. offset must between 0 and content size.</param>
		/// <param name="length">Size for reading. length is -1 means that read to the end of the chunk.</param>
		/// <returns> read bytes. </returns>
		abstract public byte[] ReadChunkBytes(long offset, long length);
		abstract public void Release();
	}
}
