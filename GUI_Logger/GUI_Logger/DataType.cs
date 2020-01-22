using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;

namespace GUI_Logger
{
    enum LOGGER_RT_SEVERITY
    {
        LOGGER_RT_SEVERITY_CRITICAL,
        LOGGER_RT_SEVERITY_ERROR,
        LOGGER_RT_SEVERITY_WARN,
        LOGGER_RT_SEVERITY_LOG,
        LOGGER_RT_SEVERITY_FLOW,
        LOGGER_RT_SEVERITY_INFO,
        LOGGER_RT_SEVERITY_DEBUG,

        LOGGER_RT_NUM_OF_SEVERITY
    };

    enum LOGGER_RT_SERVICE
    {
        LOGGER_RT_GAS_SERVICE,
        LOGGER_RT_CLIMATE_CONTROL_SERVICE,
        LOGGER_RT_TIRE_PRESSURE_SERVICE,

        LOGGER_RT_NUM_OF_SERVICES
    }

    //struct element
    //{
    //    LOGGER_RT_SEVERITY[] severityMsg;
    //    string textMsg;
    //};

    //struct dataSend
    //{
    //    element elementMsg;
    //    LOGGER_RT_SERVICE serviceMsg;
    //};

    //struct udpReceivedSeverity
    //{
    //    LOGGER_RT_SEVERITY severityMsg;
    //    LOGGER_RT_SERVICE serviceMsg;
    //};

    public partial class DataType_cs : Telerik.WinControls.UI.RadForm
    {
        
        public DataType_cs()
        {
            InitializeComponent();
        }
    }
}
