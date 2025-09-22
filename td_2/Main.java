public class Main {
    
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Main <number_of_threads>");
            return;
        }

        int N = 75000;
        int K = Integer.parseInt(args[0]);

        MonThread[] threads = new MonThread[K];
        for (int i = 0; i < K; i++) {
            threads[i] = new MonThread(i, N, K);
            threads[i].start();
        }

        for (int i = 0; i < K; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        float globalMax = 0;
        int globalMaxX = 0;
        int globalMaxY = 0;

        for (int i = 0; i < K; i++) {
            if (threads[i].getMax() > globalMax) {
                globalMax = threads[i].getMax();
                globalMaxX = threads[i].getMaxX();
                globalMaxY = threads[i].getMaxY();
            }
        }

        System.out.printf("Maximum value: %f at (%d, %d)\n", globalMax, globalMaxX, globalMaxY);
    }
}