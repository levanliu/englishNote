/*******************************************************************************
 * Copyright (c) 2014 Advantest. All rights reserved.
 *
 * Contributors:
 *     Advantest - initial API and implementation
 *******************************************************************************/
package com.advantest.itee.measurement.core.job;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.jobs.IJobChangeListener;
import org.eclipse.core.runtime.jobs.ISchedulingRule;
import org.eclipse.core.runtime.jobs.Job;

import com.advantest.itee.measurement.core.MeasurementCorePlugin;
import com.google.common.base.Strings;

/**
 * @author leenshi
 *
 */
public abstract class MeasurementJob extends Job {

    private String eventType;

    private IJobChangeListener listener;

    /**
     * internal event : problem
     */
    public static final String INTL_EVNT_PROBLEM = "INTL:PROBLEM";

    /**
     * internal event : prop origin
     */
    public static final String INTL_EVNT_ORIGIN = "INTL:PROP_ORIGIN";

    /**
     * internal event : rerun measurement
     */
    public static final String INTL_EVNT_RERUN = "INTL:RERUN";

    /**
     * internal event : bind measurement
     */
    public static final String INTL_EVNT_BIND = "INTL:BIND";

    /**
     * internal event : edit property
     */
    public static final String INTL_EVNT_EDIT = "INTL:EDIT";

    /**
     * internal event : toggle HW default enabled
     */
    public static final String INTL_EVNT_HWDEFAULT = "INTL:HW_DEFAULT";

    /**
     * internal event : init measurement view (open measurement view)
     */
    public static final String INTL_EVNT_INIT = "INTL:INIT";

    /**
     * Measurement job family
     */
    public final static Object FAMILY = new Object();

    /**
     *
     */
    public final static ISchedulingRule mvJobRule = new MeasurementJobRule();

    /**
     * Add the ruler to make sure jobs to update data from DUS run sequentially
     *
     */
    private static class MeasurementJobRule implements ISchedulingRule {
        @Override
        public boolean contains(ISchedulingRule rule) {
            return rule instanceof MeasurementJobRule;
        }

        @Override
        public boolean isConflicting(ISchedulingRule rule) {
            return rule instanceof MeasurementJobRule;
        }
    }

    /**
     * @param name
     *            job name
     */
//    public MeasurementJob(String name) {
//        this(null, name);
//    }

    /**
     * @param eventType event type
     * @param name
     *            job name
     */
    public MeasurementJob(String eventType, String name) {
        super(name);
        setRule(mvJobRule);
        this.eventType = Strings.isNullOrEmpty(eventType) ? "\t" : eventType;
    }

    @Override
    public boolean belongsTo(Object family) {
        return FAMILY == family;
    }

    @Override
    protected IStatus run(IProgressMonitor monitor) {
        try {
            MeasurementCorePlugin.getTimer().jobStarted(toString(), eventType);

            if (monitor.isCanceled()) {
                return Status.CANCEL_STATUS;
            }
            preRun(monitor);
            if (monitor.isCanceled()) {
                return Status.CANCEL_STATUS;
            }
            IStatus status = performRun(monitor);
            postRun();
            return status;

        } finally {
            MeasurementCorePlugin.getTimer().jobFinished(toString(), eventType);
        }
    }

    /**
     * Runs any operation before performing run.
     * @param monitor TODO
     *
     */
    protected void preRun(IProgressMonitor monitor) {
        // default implementation
    }


    protected abstract IStatus performRun(IProgressMonitor monitor);

    /**
     * Runs any operation after performing run.
     */
    protected void postRun() {
        // default implementation
    }

    /**
     * @return Returns the eventType.
     */
    public String getEventType() {
        return eventType;
    }

    /**
     * @param eventType The eventType to set.
     */
    protected void setEventType(String eventType) {
        this.eventType = eventType;
    }

    /**
     * @param listener2 listener
     */
    public void addJobChangeListener2(IJobChangeListener listener2) {
        if (this.listener == null) {
            this.listener = listener2;
            addJobChangeListener(listener2);
        }
    }

    public void clearEventType() {
        // do nothing
    }
}
