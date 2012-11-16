package mas.math.random;

import jsc.distributions.*;

public class NormalRandomizer implements Randomizer {
	
	public NormalRandomizer( double miu, double delta ){
		norm = new Normal(miu, delta);
	}
	
	@Override
	public double nextDouble() {
		return norm.random();
	}

	@Override
	public float nextFloat() {
		return (float)nextDouble();
	}

	@Override
	public int nextInt() {
		return (int)nextDouble();
	}

	@Override
	public int normalize(double v) {
		return 0;
	}

	private Normal norm;
}
