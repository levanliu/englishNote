/*******************************************************************************
 * Copyright (c) 2021 Advantest. All rights reserved.
 *
 * Contributors:
 *     Advantest - initial API and implementation
 *******************************************************************************/
package com.advantest.itee.measurement.core.job;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.lang.StringUtils;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.jobs.Job;

import com.advantest.itee.measurement.core.MeasurementCorePlugin;
import com.advantest.itee.measurement.core.util.DebugPerformanceTrace;
import com.verigy.itee.core.util.EnvironmentVariables;

/**
 * @author justis
 *
 */
public class MeasurementTimer {

    /**
     * job title
     */
    private static final String JOB_NAME = "Calculate Measurement View Refresh time";

    /**
     * wait time out
     */
    private static final int WAIT_TIME_OUT = 10_000;

    private final Map<String, Long> jobStartTimeMap = new ConcurrentHashMap<>();

    private boolean calcRefreshTime = false;

    private volatile long startTime = 0;

    private volatile long latestFinishTime = 0;

    /**
     * the duration starting from the first job, and ending with the last job
     */
    private int totalRefreshTime = 0;

    private boolean collectMoreData = false;

    private Map<String, Integer> moreData = new HashMap<>();

    /**
     * the duration while MV is doing nothing
     */
    private int idleTime = 0;

    private final Job calcTotalTimeJob = new Job(JOB_NAME) {

        @Override
        protected IStatus run(IProgressMonitor monitor) {
            if (collectMoreData) {
                DebugPerformanceTrace.getInstance().setCachePerformanceData(true);
            }
            idleTime = 0;
            while (isMeasurementJobActive()) {
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    // do nothing
                }
            }

            totalRefreshTime = (int) (latestFinishTime - startTime);
            startTime = 0;
            latestFinishTime = 0;
            if (isPrintToConsole() ) {
                System.out.println("Total cost: " + totalRefreshTime + "ms, MV cost: " + getMVRefreshTime() + "ms");
            }

            if (collectMoreData) {
                moreData = DebugPerformanceTrace.getInstance().getPerformanceData();
                DebugPerformanceTrace.getInstance().setCachePerformanceData(false);
                DebugPerformanceTrace.getInstance().clearPerformanceData();
            }

            return Status.OK_STATUS;
        }

        private boolean isMeasurementJobActive() {
            long waitStart = System.currentTimeMillis();
            int waitTime = 0;
            while (!isTimeOut(waitTime)) {
                if (!jobStartTimeMap.isEmpty()) {
                    if (waitTime > 150) { // ignore the wait time which is less than 150ms
                        idleTime = idleTime + waitTime;
                    }
                    return true;
                }

                // idle
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    // do nothing
                }

                waitTime = (int) (System.currentTimeMillis() - waitStart);
            }

            // timeout
            return false;
        }

        /**
         * @param waitStart
         * @return
         */
        private boolean isTimeOut(long waitTime) {
            return waitTime > WAIT_TIME_OUT;
        }
    };

    /**
     *
     */
    public MeasurementTimer() {
        calcTotalTimeJob.setSystem(true);
        calcRefreshTime = Boolean.parseBoolean(EnvironmentVariables.XOC_MONITOR_MV.get());
    }

    /**
     * @return true if print to console
     */
    protected boolean isPrintToConsole() {
        return isCalcRefreshTime();
    }

    /**
     * @param calcRefreshTime The calcRefreshTime to set.
     */
    public void setCalcRefreshTime(boolean calcRefreshTime) {
        this.calcRefreshTime = calcRefreshTime;
    }

    /**
     * @return Returns the calcRefreshTime.
     */
    public boolean isCalcRefreshTime() {
        return calcRefreshTime;
    }

    /**
     * @param jobId job id
     * @param eventType event type
     */
    public void jobStarted(String jobId, String eventType) {
        long start = System.currentTimeMillis();
        jobStartTimeMap.put(jobId, Long.valueOf(start));

        String message = StringUtils.rightPad("JOB START", 19) + ": " + StringUtils.rightPad(jobId, 40) + " EVENT: "
                + StringUtils.rightPad(eventType, 28);
        MeasurementCorePlugin.logDebug(message);

        if (calcRefreshTime && !isRunning()) {
            startTime = start;
            calcTotalTimeJob.schedule();
        }
    }

    /**
     * @param jobId job id
     * @param eventType event type
     */
    public void jobFinished(String jobId, String eventType) {
        Long start = jobStartTimeMap.get(jobId);
        long finish = System.currentTimeMillis();
        latestFinishTime = finish;
        jobStartTimeMap.remove(jobId);
        long executionTime = 0;

        if (start != null) {
            executionTime = finish - start.longValue();
        }

        String message = StringUtils.rightPad("JOB FINISH(" + executionTime + "ms)", 19) + ": "
                + StringUtils.rightPad(jobId, 40) + " EVENT: " + StringUtils.rightPad(eventType, 28);
        MeasurementCorePlugin.logDebug(message);
    }

    /**
     * @return Returns the totalRefreshTime.
     */
    public int getTotalRefreshTime() {
        return totalRefreshTime;
    }

    /**
     * @return Returns the idleTime.
     */
    public int getMVRefreshTime() {
        return totalRefreshTime - idleTime;
    }

    /**
     * @return true if the timer is running
     */
    public boolean isRunning() {
        return calcTotalTimeJob.getState() != Job.NONE;
    }

    /**
     * @param collectMoreData The collectMoreData to set.
     */
    public void setCollectMoreData(boolean collectMoreData) {
        this.collectMoreData = collectMoreData;
    }

    /**
     * @return Returns the moreData.
     */
    public Map<String, Integer> getMoreData() {
        return moreData;
    }
}
