import java.util.concurrent.Semaphore;
import java.util.Random;

//Solving the mutual exclusion("mutex") problem using Semaphore class
class Process2 extends Thread {
    private static final Random rand = new Random();
    private int id;
    private Semaphore sem;

    public Process2(int i, Semaphore s) {
        id = i;
        sem = s;
    }

    private void busy() {
        try {
            sleep(rand.nextInt(500));
//            sleep(300);
        } catch (InterruptedException e) {
        }
    }

    private void noncritical() {
        System.out.println("Thread " + id + " is NON critical");
        busy();
    }

    private void critical() {
        System.out.println("Thread " + id + " entering critical section");
        busy();
        System.out.println("Thread " + id + " leaving critical section");
    }

    public void run() {
        for (int i = 0; i < 2; ++i) {
            noncritical();
            try {
                sem.acquire();      // Each acquire() blocks if necessary until a permit is available, and then takes it.
            } catch (InterruptedException e) {
            }
            critical();
            sem.release();          // Each release() adds a permit, potentially releasing a blocking acquirer.
        }
    }
}

public class semaphoreSimulation {
    public static void main(String[] args) {
        final int N = 4;
        System.out.println("Busy waiting...");
        //Semaphore(int permits, boolean fair)
        Semaphore sem = new Semaphore(N, true);
        Process2[] p = new Process2[N * 2]; //更改處
        for (int i = 0; i < 2 * N; i++) {
            p[i] = new Process2(i, sem);
            p[i].start();
        }
    }
}
