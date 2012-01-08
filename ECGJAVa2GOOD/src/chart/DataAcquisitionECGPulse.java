/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package chart;

/**
 *
 * @author francispapineau
 */
/*
 *
 *  RandomDataCollector.java  jchart2d
 *  Copyright (C) Achim Westermann, created on 10.12.2004, 15:04:16
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 * 
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  If you modify or optimize the code in a useful way please let me know.
 *  Achim.Westermann@gmx.de
 *
 */

import info.monitorenter.gui.chart.ITrace2D;
import info.monitorenter.gui.chart.TracePoint2D;
import info.monitorenter.gui.chart.io.ADataCollector;

/**
 * A proof of concept dummy implementation for the supertype.
 * <p>
 * 
 * Only collects random values with timestamp on the x axis. The timestamp is
 * related to the time when this instance is instantiated to make it a lower
 * value (offset to start). implementation for exact timestamps that may be
 * formatted with java.text.DateFormat instances.
 * <p>
 * 
 * @author <a href="mailto:Achim.Westermann@gmx.de">Achim Westermann </a>
 * 
 * @version $Revision: 1.6 $
 */

public class DataAcquisitionECGPulse extends ADataCollector{
    

  /** The start time of this collector. */
  private long m_starttime = System.currentTimeMillis();

  /** The last y value added. */
  private double m_y = 0.0;
  public static double Choice;

  /**
   * Creates a collector that collectes every latency ms a point and adds it to
   * the trace.
   * <p>
   * 
   * @param trace
   *          the trace to add points to.
   * 
   * @param latency
   *          the interval for collection of points.
   */
  public DataAcquisitionECGPulse(final ITrace2D trace, final int latency) {
    super(trace, latency);
  }

  /**
   * @see ADataCollector#collectData()
   */
  @Override
  public TracePoint2D collectData() {

      
    this.m_y = ecgjava2.SplitParse.getECGPulse();
    
    return new TracePoint2D(((double) System.currentTimeMillis() - this.m_starttime), this.m_y);
  }
  
}