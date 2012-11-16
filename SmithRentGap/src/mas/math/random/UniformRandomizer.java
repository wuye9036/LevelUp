package mas.math.random;

import java.util.Random;

public class UniformRandomizer implements Randomizer{

	public UniformRandomizer(double min, double max){
		this.min = min;
		this.max = max;
		
		rand = new Random();
		rand.setSeed(System.nanoTime());
	}
	
	static public UniformRandomizer CreateAsAvgSd(double avg, double sd){
		double max = avg + Math.sqrt(3) * sd;
		double min = avg - Math.sqrt(3) * sd;
		
		return new UniformRandomizer( min, max );
	}
	
	static public UniformRandomizer CreateAsMidRange( double mid, double range ){
		return new UniformRandomizer( mid - range, mid + range );
	}
	
	@Override
	public double nextDouble() {
		return min + rand.nextDouble() * (max - min);
	}

	@Override
	public float nextFloat() {
		return (float)min + rand.nextFloat() * ((float)max - (float)min);
	}
	
	Random rand;
	
	double min;
	double max;
	@Override
	public int normalize(double v) {
		return (int)((v - min) / ( max - min ));
	}

	@Override
	public int nextInt() {
		return (int)(Math.floor(nextDouble()));
	}
}
