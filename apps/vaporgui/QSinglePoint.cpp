#include "QSinglePoint.h"
#include "ui_QSinglePoint.h"

// for debug
#include <iostream>
#include <cassert>

QSinglePoint::QSinglePoint(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::QSinglePoint)
{
    _ui->setupUi(this);

    SetDimensionality( 3 );     // default to have 3 dimensions

    _ui->xSliderEdit->SetText( QString::fromAscii("X") );
    _ui->ySliderEdit->SetText( QString::fromAscii("Y") );
    _ui->zSliderEdit->SetText( QString::fromAscii("Z") );
    _ui->tSliderEdit->SetText( QString::fromAscii("T") );

    // Connect signals and slots
    connect(_ui->xSliderEdit,  SIGNAL(valueChanged(double)),
            this,              SLOT( _coordinateChanged(double)));
    connect(_ui->ySliderEdit,  SIGNAL(valueChanged(double)),
            this,              SLOT( _coordinateChanged(double)));
    connect(_ui->zSliderEdit,  SIGNAL(valueChanged(double)),
            this,              SLOT( _coordinateChanged(double)));
    connect(_ui->tSliderEdit,  SIGNAL(valueChanged(double)),
            this,              SLOT( _coordinateChanged(double)));
    
}

QSinglePoint::~QSinglePoint()
{
    delete _ui;
}
    
void QSinglePoint::_coordinateChanged( double value )  // value isn't used though
{
    emit PointUpdated();
}

    
void QSinglePoint::SetDimensionality( int dim )
{
    assert( dim >= 2 );
    assert( dim <= 4 );
    _dimensionality = dim;
    _ui->xSliderEdit->setVisible( true );
    _ui->ySliderEdit->setVisible( true );
    _ui->zSliderEdit->setVisible( false );
    _ui->tSliderEdit->setVisible( false );
    if( dim >= 3 )
        _ui->zSliderEdit->setVisible( true );
    if( dim >= 4 )
        _ui->tSliderEdit->setVisible( true );
}

int  QSinglePoint::GetDimensionality( )
{
    return _dimensionality;
}
    
void QSinglePoint::GetCurrentPoint( std::vector<double>& point )
{
    point.clear();
    point.push_back( _ui->xSliderEdit->GetCurrentValue() );
    point.push_back( _ui->ySliderEdit->GetCurrentValue() );
    if( _dimensionality >= 3 )
        point.push_back( _ui->zSliderEdit->GetCurrentValue() );
    if( _dimensionality >= 4 )
        point.push_back( _ui->tSliderEdit->GetCurrentValue() );
}
    
void QSinglePoint::SetExtents( const std::vector<double>& min, const std::vector<double>& max )
{
    assert( min.size() == _dimensionality );
    assert( max.size() == _dimensionality );

    _ui->xSliderEdit->SetExtents( min[0], max[0] );
    _ui->ySliderEdit->SetExtents( min[1], max[1] );
    if( _dimensionality >= 3 )
        _ui->zSliderEdit->SetExtents( min[2], max[2] );
    if( _dimensionality >= 4 )
        _ui->tSliderEdit->SetExtents( min[3], max[3] );
}