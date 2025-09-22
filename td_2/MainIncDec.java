public class MainIncDec {
    public static void main(String[] args) {
        int N = 1000 * 1000;
        Variable var = new Variable();
        ThreadInc tPlus = new ThreadInc(N, +1, var);
        tPlus.start();

        ThreadInc tMoins = new ThreadInc(N, -1, var);
        tMoins.start();

        try {
            tMoins.join();
            tPlus.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Valeur finale de x : " + var.getX());
    }
}