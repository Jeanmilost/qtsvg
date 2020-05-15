#pragma once

// qt
#include <QTimer>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QSvgRenderer>

/**
* Animated SVG image for Qt Quick
*@author JMR
*/
class WQtSVGImage : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(QString sourceName READ sourceName WRITE setSourceName)

    public:
        /**
        * Constructor
        *@param pParent - parent object, can be 0
        */
        WQtSVGImage(QQuickItem* pParent = 0);

        virtual ~WQtSVGImage();

        /**
        * Get the source file name
        *@returns the source file name
        */
        virtual QString sourceName() const;

        /**
        * Set the source file name
        *@param value - the source file name
        */
        virtual void setSourceName(const QString& value);

        /**
        * Paint the image
        *@param pPainter - the painter
        */
        virtual void paint(QPainter* pPainter);

    private:
        QSvgRenderer* m_pSvgRenderer;
        QTimer*       m_pTimer;
        QString       m_Source;

        /**
        * Called when the timer ticks
        */
        void onTimeout();
};
