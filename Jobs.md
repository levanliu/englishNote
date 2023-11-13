### Eclipse Jobs

```java
=// 观察者接口
public interface JobCompletionObserver {
    void jobCompleted();
}

// CustomJob类
public class CustomJob extends Job {
    private JobCompletionObserver observer;

    public CustomJob(String name, JobCompletionObserver observer) {
        super(name);
        this.observer = observer;
    }

    @Override
    protected IStatus run(IProgressMonitor monitor) {
        // 这里是你的job的实际逻辑

        // 在job完成后，通知观察者
        if (observer != null) {
            observer.jobCompleted();
        }

        return Status.OK_STATUS;
    }
}

// main线程
public class MainClass implements JobCompletionObserver {
    public void main(String[] args) {
        CustomJob job = new CustomJob("My Job", this);
        job.schedule();  // 开始job
    }

    @Override
    public void jobCompleted() {
        System.out.println("Job completed");
        // 这里是Job完成后的处理逻辑
    }
}

```