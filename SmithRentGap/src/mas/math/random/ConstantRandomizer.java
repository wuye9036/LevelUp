package mas.math.random;

public class ConstantRandomizer implements Randomizer {
	public ConstantRandomizer(double c){
		this.c = c;
	}
	
	@Override
	public double nextDouble() {
		return c;
	}

	@Override
	public float nextFloat() {
		return (float)c;
	}
	
	@Override
	public int nextInt() {
		return (int)(Math.floor(c));
	}	
	
	private double c;

	@Override
	public int normalize(double v) {
		return (int)(v / c);
	}


}
