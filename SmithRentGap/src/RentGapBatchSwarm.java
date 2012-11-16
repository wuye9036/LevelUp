import swarm.Globals;
import swarm.Selector;
import swarm.activity.ActionGroup;
import swarm.activity.ActionGroupImpl;
import swarm.activity.Activity;
import swarm.activity.Schedule;
import swarm.activity.ScheduleImpl;
import swarm.defobj.Zone;
import swarm.objectbase.Swarm;
import swarm.objectbase.SwarmImpl;


public class RentGapBatchSwarm extends SwarmImpl {
	public ExperimentRecorder recorder;
	public String expName;
	
	public ActionGroup batchActions;
	public Schedule outputSchedule;
	public Schedule stoppingSchedule;
	
	public RentGapModelSwarm model;
	
	public int stopTime;
	
	public RentGapBatchSwarm(Zone aZone, ExperimentRecorder recorder, String expName){
		super( aZone );
		model = new RentGapModelSwarm(getZone());
		this.recorder = recorder;
		this.expName = expName;
	}
	
	public Object buildObjects(){
		super.buildObjects();	
		model.buildObjects();
		
		return this;
	}
	
	public Object buildActions(){
		super.buildActions();
		model.buildActions();
		
		batchActions = new ActionGroupImpl( getZone() );
		try {
			batchActions.createActionTo$message(
					recorder, 
					new Selector(recorder.getClass(), "update", false)
					);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		outputSchedule = new ScheduleImpl(getZone(), 1);
		outputSchedule.at$createAction(0, batchActions);
		
		stoppingSchedule = new ScheduleImpl(getZone(), true);
		try {
			stoppingSchedule.at$createActionTo$message(
					stopTime, this,
					new Selector(getClass(), "stopRunning", false));
		} catch (Exception e) {
			e.printStackTrace();
		}
		return this;
	}
	
	public Activity activateIn( Swarm swarmContext ){
		super.activateIn(swarmContext);
		model.activateIn(this);
		stoppingSchedule.activateIn(this);
		outputSchedule.activateIn(this);
		
		return getActivity();
	}
	
	public Object go(){
		recorder.beginExperiment(model, expName);
		getActivity().getSwarmActivity().run();
		recorder.endExperiment();
		
		return getActivity().getStatus();
	}
	
	public Object stopRunning(){
		Globals.env.getCurrentSwarmActivity ().terminate (); 
		return this;
	}
}
