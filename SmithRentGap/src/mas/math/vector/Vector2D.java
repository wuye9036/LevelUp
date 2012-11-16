package mas.math.vector;

public class Vector2D<T extends java.lang.Number> extends Vector{
	public Vector2D(T x, T y){
		this.x = x;
		this.y = y;
	}
	
	public Vector2D<T> clone(){
		return new Vector2D<T>(x, y);
	}
	
	public T x;
	public T y;
}