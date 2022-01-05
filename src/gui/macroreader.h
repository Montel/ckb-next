#ifndef MACROREADER_H
#define MACROREADER_H

#include <QObject>
#include <QFile>
#include <QLocalSocket>
#include <QElapsedTimer>

class MacroReader : public QObject {
Q_OBJECT

public:
    MacroReader(const QStringList& macroPaths);
    ~MacroReader();
    inline void resetTimer() { (void)keyStrokeTime(); }

private:
    QStringList _macroPaths;
    QList<QFile*> fhandles;
    QList<QLocalSocket*> fnotifiers;
    QElapsedTimer* timer;
    void macroDataReceived(QLocalSocket* f);
    qint64 keyStrokeTime();
    static constexpr int MACRO_ARRAY_LEN = 24;

Q_SIGNALS:
    void macroLineRead(const QString &key, qint64 ustime, bool keydown);
    void macroReadError(const QString &key, const QString &modifiers);

public Q_SLOTS:
    void translateQKeyEvent(int keycode, bool down, Qt::KeyboardModifiers modifiers);
};

#endif // MACROREADER_H
