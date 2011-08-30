/*=========================================================================

   Program: ParaView
   Module:    pqStandardSummaryPanelImplementation.cxx

   Copyright (c) 2005-2008 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#include "pqChartSummaryDisplayPanel.h"

#include "pqPlotSettingsModel.h"
#include "pqPipelineRepresentation.h"
#include "pqView.h"
#include "vtkSMProxy.h"
#include "vtkSMDomain.h"
#include "vtkSMProperty.h"

#include <QFormLayout>
#include <QComboBox>

//-----------------------------------------------------------------------------
pqChartSummaryDisplayPanel::pqChartSummaryDisplayPanel(pqRepresentation *representation, QWidget *parent)
  : QWidget(parent)
{
  this->Representation = representation;

  vtkSMProxy *proxy = representation->getProxy();
  const char *name = proxy->GetXMLName();

  QFormLayout *layout = new QFormLayout;

  // setup the attribute mode selector
  this->AttributeSelector = new QComboBox(this);
  this->AttributeSelector->addItem(QIcon(QString(":/pqWidgets/Icons/pqPointData16.png")), "Point Data");
  this->AttributeSelector->addItem(QIcon(QString(":/pqWidgets/Icons/pqCellData16.png")), "Cell Data");
  this->AttributeSelector->addItem(QIcon(QString(":/pqWidgets/Icons/pqPointData16.png")), "Vertex Data");
  this->AttributeSelector->addItem(QIcon(QString(":/pqWidgets/Icons/pqRamp24.png")), "Edge Data");
  this->AttributeSelector->addItem(QIcon(QString(":/pqWidgets/Icons/pqSpreadsheet16.png")), "Row Data");
  this->AttributeModeAdaptor = new pqSignalAdaptorComboBox(this->AttributeSelector);
  this->Links.addPropertyLink(this->AttributeModeAdaptor,
                              "currentText",
                              SIGNAL(currentTextChanged(const QString&)),
                              proxy,
                              proxy->GetProperty("AttributeType"));
  layout->addRow("Attribute Mode:", this->AttributeSelector);

  if(strcmp(name, "ParallelCoordinatesRepresentation") != 0)
    {
    // setup the x-series selector
    this->UseArrayIndex = new QCheckBox(this);
    this->UseArrayIndex->setChecked(true);
    connect(this->UseArrayIndex,
            SIGNAL(toggled(bool)),
            this,
            SLOT(useXAxisIndiciesToggled(bool)));

    this->Links.addPropertyLink(this->UseArrayIndex,
                                "checked",
                                SIGNAL(toggled(bool)),
                                proxy,
                                proxy->GetProperty("UseIndexForXAxis"));

    layout->addRow("Use Indicies for X-Axis:", this->UseArrayIndex);

    this->XSeriesSelector = new QComboBox(this);
    this->XSeriesSelector->setEnabled(false);
    this->XAxisArrayAdaptor = new pqSignalAdaptorComboBox(this->XSeriesSelector);
    this->XAxisDomain = new pqComboBoxDomain(this->XSeriesSelector,
                                             proxy->GetProperty("XArrayName"));
    this->Links.addPropertyLink(this->XAxisArrayAdaptor,
                                "currentText",
                                SIGNAL(currentTextChanged(const QString&)),
                                proxy,
                                proxy->GetProperty("XArrayName"));
    layout->addRow("X Axis Series:", this->XSeriesSelector);
    }

  // setup the y-series selector
  this->PlotSettingsModel = new pqPlotSettingsModel(this);
  this->PlotSettingsModel->setRepresentation(qobject_cast<pqDataRepresentation*>(representation));

  this->YSeriesSelector = new QComboBox(this);
  connect(this->YSeriesSelector, SIGNAL(activated(int)), this, SLOT(ySeriesChanged(int)));
  this->YSeriesSelector->setModel(this->PlotSettingsModel);

  layout->addRow("Y Axis Series:", this->YSeriesSelector);

  this->setLayout(layout);
}

//-----------------------------------------------------------------------------
void pqChartSummaryDisplayPanel::ySeriesChanged(int index)
{
  // toggle the enabled state of the series at the selected index
  bool enabled = this->PlotSettingsModel->getSeriesEnabled(index);
  this->PlotSettingsModel->setSeriesEnabled(index, !enabled);

  // re-render the view
  this->Representation->renderViewEventually();
}

//-----------------------------------------------------------------------------
void pqChartSummaryDisplayPanel::useXAxisIndiciesToggled(bool enabled)
{
  this->XSeriesSelector->setEnabled(!enabled);
}
