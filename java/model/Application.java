package model;

public class Application {
    private static Model model;

    public static void main(String[] args) {
		//model = new Model("/home/cloud/proj/pinswrapper/examples/iprotocol.2.dve");		
		model = new Model("/home/cloud/proj/pinswrapper/examples/Philosophers-5.pnml");

		System.out.print("Dependency Matrix: \n");
        for (int[] ia : model.getDependencyMatrix()) {
            for (int e : ia) {
                System.out.print(e + " ");                
            }
            System.out.println();
        }
        System.out.print("\n");
		System.out.print("Initial state: ");
		for (int e : model.getInitialState()) {
			System.out.print(e);
		}
		System.out.println("\n");
		for (int i = 0; i < model.getNumOfTransitions(); i++) {
			if(model.getNextState(i, model.getInitialState()) > 0){
				System.out.println(" by transition " + i);
			}
		}
		System.out.println("");
    }
}
