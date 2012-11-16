package mas.math.vector;

public class Vector {
	public static <T extends java.lang.Number> float DistanceSq(Vector2D<T> src, Vector2D<T> dest){
		float xDist = src.x.floatValue() - dest.x.floatValue();
		float yDist = src.y.floatValue() - dest.y.floatValue();
		
		return xDist * xDist + yDist * yDist;
	}
	
	public static <T extends java.lang.Number> float Distance(Vector2D<T> src, Vector2D<T> dest){
		return (float)Math.sqrt(DistanceSq(src, dest));
	}
}
