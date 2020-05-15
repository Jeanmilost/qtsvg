#include "WQtSVGImage.h"

// qt
#include <QFile>

//---------------------------------------------------------------------------
WQtSVGImage::WQtSVGImage(QQuickItem* pParent) :
    QQuickPaintedItem(pParent),
    m_pSvgRenderer(NULL),
    m_pTimer(NULL)
{
    // create a timer and link it with the onTimeout() function
    m_pTimer = new QTimer();
    (void)connect(m_pTimer, &QTimer::timeout, this, &WQtSVGImage::onTimeout);
}
//---------------------------------------------------------------------------
WQtSVGImage::~WQtSVGImage()
{
    if (m_pTimer)
        delete m_pTimer;

    if (m_pSvgRenderer)
        delete m_pSvgRenderer;
}
//---------------------------------------------------------------------------
QString WQtSVGImage::sourceName() const
{
    return m_Source;
}
//---------------------------------------------------------------------------
void WQtSVGImage::setSourceName(const QString& value)
{
    // stop the running timer
    m_pTimer->stop();

    if (m_pSvgRenderer)
        delete m_pSvgRenderer;

    #ifdef VISUAL_STUDIO
        m_Source = value;
    #else
        m_Source = ":/" + value;
    #endif

    // source file exists?
    if (!QFile::exists(m_Source))
    {
        m_pSvgRenderer = NULL;
        return;
    }

    // create a svg renderer
    m_pSvgRenderer = new QSvgRenderer();
    m_pSvgRenderer->load(m_Source);

    // start the timer
    m_pTimer->setInterval(20);
    m_pTimer->start();
}
//---------------------------------------------------------------------------
void WQtSVGImage::paint(QPainter* pPainter)
{
    // paint the current svg frame
    if (m_pSvgRenderer)
        m_pSvgRenderer->render(pPainter);
}
//---------------------------------------------------------------------------
void WQtSVGImage::onTimeout()
{
    update();
}
//---------------------------------------------------------------------------
