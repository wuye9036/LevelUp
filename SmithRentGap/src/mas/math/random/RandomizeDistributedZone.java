package mas.math.random;

public class RandomizeDistributedZone extends DistributedZone {

	public RandomizeDistributedZone(Randomizer rand, int width, int height) {
		super(rand, width, height);
	}

	@Override
	public float getValue(int x, int y) {
		return rand.nextFloat();
	}

	@Override
	public float getAverage() {
		return 0.0f;
	}

	@Override
	public float getMax() {
		return 0.0f;
	}

	@Override
	public float getMin() {
		return 0.0f;
	}

	@Override
	public float getStandardDev() {
		return 0.0f;
	}

}
