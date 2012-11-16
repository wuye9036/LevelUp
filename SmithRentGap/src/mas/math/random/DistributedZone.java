package mas.math.random;

public abstract class DistributedZone {
	public DistributedZone(Randomizer rand, int width, int height){
		this.rand = rand;
		this.width = width;
		this.height = height;
	}
	
	public abstract float getValue(int x, int y);
	public abstract float getMax();
	public abstract float getMin();
	public abstract float getStandardDev();
	public abstract float getAverage();
	
	protected Randomizer rand;
	protected int width;
	protected int height;
}
