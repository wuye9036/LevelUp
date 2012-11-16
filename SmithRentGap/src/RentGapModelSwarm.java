import mas.math.random.ConstantRandomizer;
import mas.math.random.DistributedZone;
import mas.math.random.RandomizeDistributedZone;
import swarm.Selector;
import swarm.activity.ActionGroup;
import swarm.activity.ActionGroupImpl;
import swarm.activity.Activity;
import swarm.activity.Schedule;
import swarm.activity.ScheduleImpl;
import swarm.defobj.Zone;
import swarm.objectbase.Swarm;
import swarm.objectbase.SwarmImpl;


public class RentGapModelSwarm extends SwarmImpl {
	public ActionGroup modelActions;
	public Schedule modelSchedule;
	
	public Developer developer;
	public ResearchArea area;
	
	public float developerCapital;
	public float maintainceThreshold;
	public int worldSize;
	public float constructionCost;
	public float neighbourRadius;
	public DistributedZone potentialRentGen;
	// public float potentialRent;
	
	public int snapFrequency = 100;
	
	public RentGapModelSwarm(Zone zone){
		super(zone);
		
		developerCapital = 8000.0f;
		maintainceThreshold = 0.8f;
		worldSize = 41;
		constructionCost = 1000.0f;
		neighbourRadius = 1.5f;
		potentialRentGen = new RandomizeDistributedZone( new ConstantRandomizer(3000.0), worldSize, worldSize );
	}
	
	public Object buildObjects(){
		area = new ResearchArea(getZone(), worldSize, worldSize, this);
		developer = new Developer(area, this);
		
		return this;
	}
	
	public Object buildActions(){
		modelActions = new ActionGroupImpl( getZone() );
		try{
			modelActions.createActionTo$message(developer, new Selector( developer.getClass(), "update", false));
			modelActions.createActionTo$message(area, new Selector(area.getClass(), "update", false));
		} catch (Exception e){
			System.err.println("Exception Developer Step Or World Step: " + e.getMessage() );
		}
		
		modelSchedule = new ScheduleImpl( getZone(), 1 );
		modelSchedule.at$createAction(0, modelActions);
		
		return this;
	}
	
	public Activity activateIn(Swarm swarmContext){
		super.activateIn(swarmContext);
		modelSchedule.activateIn(this);
		return getActivity();
	}
}
