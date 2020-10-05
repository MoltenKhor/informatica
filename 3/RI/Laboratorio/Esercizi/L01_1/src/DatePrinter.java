import java.util.Calendar;

public class DatePrinter {
    public static void main(String args[]){
        while(true){
            System.out.println(Calendar.getInstance().getTime());
            System.out.println(Thread.currentThread().getName());
            try{
                Thread.sleep(2000);
            }catch(InterruptedException e){
                System.out.println("Sleep Interrotta");
                return;
            }
        }
    }
}
