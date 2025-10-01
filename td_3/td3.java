abstract class Variable {
    protected int x = 0;

    abstract public void inc(int i);

    public int getX() {
        return this.x;
    }
}

class VariableUnprotected extends Variable {
    public VariableUnprotected() {
        super();
    }

    @Override
    public void inc(int i) {
        this.x += i;
    }
}

class VariableProtected extends Variable {
    public VariableProtected() {
        super();
    }

    @Override
    public synchronized void inc(int i) {
        this.x += i;
    }
}

class ThreadInc extends Thread {
    private Variable var;
    private final int N;
    private final int inc_dec; // 1 pour inc, -1 pour dec

    public ThreadInc(int N, int inc_dec, Variable var) {
        this.var = var;
        this.N = N;
        this.inc_dec = inc_dec;
    }

    public void run() {
        for (int i = 0; i < N; i++) {
                var.inc(inc_dec);
            
        }
    }
}

public class td3 {
    public static void main(String[] args) {
        int N = 1000 * 1000;
        VariableUnprotected var = new VariableUnprotected();
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

        System.out.println("Valeur finale de x Sans synchro: " + var.getX());


        /* II.5 */
        VariableProtected var2 = new VariableProtected();
        ThreadInc tPlus2 = new ThreadInc(N, +1, var2);
        ThreadInc tMoins2 = new ThreadInc(N, -1, var2);
        tPlus2.start();
        tMoins2.start();

        try {
            tMoins2.join();
            tPlus2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Valeur finale de x Avec synchro: " + var2.getX());
    }
}