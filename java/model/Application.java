package model;

import java.util.*;

public class Application {
    private static Model model;

    public static void stateCount(Model m){
    	Stack<State> stack = new Stack<State>();
    	List<State> states = new ArrayList<State>();

    	State initialState = new State(model.getInitialState());

    	states.add(initialState);
		stack.push(initialState);

		while(!stack.empty()) {
			State previousState = stack.pop();
	        for(int t = 0; t < model.getNumOfTransitions(); t++) {
	        	if(model.getNextState(t, previousState.getStateAsArray()) > 0){
	        		State s = new State(model.getNextStateResult());
	        		if(!states.contains(s)){
		        		//for (int e : s.getStateAsArray()) {
		        		//	System.out.print(e);
		        		//}
		        		//System.out.println();
	        			stack.push(s);
			    		states.add(s);
	        		}
	        	}
	        }
		}

		System.out.println(states.size());

    }

    public static void main(String[] args) {
		model = new Model("/home/cloud/proj/pinswrapper/examples/iprotocol.2.dve");		
		//model = new Model("/home/cloud/proj/pinswrapper/examples/Philosophers-5.pnml");	
		//model = new Model("/home/cloud/proj/pinswrapper/examples/elevator.3.dve");

		/*System.out.print("Dependency Matrix: \n");
        for (int[] ia : model.getDependencyMatrix()) {
            for (int e : ia) {
                System.out.print(e + " ");                
            }
            System.out.println();
        }
        System.out.print("\n");
		*/
		System.out.print("Initial state: ");
		for (int e : model.getInitialState()) {
			System.out.print(e);
		}
		System.out.println("\n");
		/*
		for (int i = 0; i < model.getNumOfTransitions(); i++) {
			if(model.getNextState(i, model.getInitialState()) > 0){
				System.out.println(" by transition " + i);
			}
		}*/
		System.out.println("");

		stateCount(model);
    }
}
