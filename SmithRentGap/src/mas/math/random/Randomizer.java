package mas.math.random;

public interface Randomizer {
	double nextDouble();
	float nextFloat();
	int nextInt();
	
	int normalize(double v);
}
