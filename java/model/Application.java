package model;

public class Application {
    private static Model model;

    public static void main(String[] args) {
		model = new Model("/home/cloud/proj/pinswrapper/examples/iprotocol.2.dve");
		//System.out.println("State vector length: " + model.getStateLength());
		//System.out.println("Number of transitions: " + model.getNumberOfTransitions() + "\n");
		System.out.print("Initial state: ");
		for (int e : model.getInitialState()) {
			System.out.print(e);
		}
		System.out.println("\n");
		for (int i = 0; i < model.getNumOfTransitions(); i++) {
			System.out.println("Transition " + i + ":" + model.getNextState(i, model.getInitialState()) + "\n");
		}
		//System.out.println("\n\n");
		//model.getNextState(model.getInitialState());
    }
}
