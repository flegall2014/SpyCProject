#ifndef TRANSLATOR_H
#define TRANSLATOR_H

// Qt
#include <QObject>
class QTranslator;

class Translator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    Translator(QObject *pParent=nullptr);

    //! Destructor
    ~Translator();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Test
    QString getEmptyString();

    //! Select language
    Q_INVOKABLE void selectLanguage(const QString &sLanguage);

signals:
    //! Language changed
    void languageChanged();

private:
    //! Translator
    QTranslator *m_pTranslator=nullptr;
};

#endif // TRANSLATOR_H
