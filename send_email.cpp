#include "send_email.h"

int PasswordSmtp::ReadFromHost()//检查接收到的数据是否符合预期
{
    sslSocket->waitForReadyRead(10000);
    QString buffer = sslSocket->readAll();//从 sslSocket 中读取所有可用的数据并存储在 buffer 中
    qDebug()<<buffer<<endl;
    if(buffer.contains(this->ExpectedReplyFromHost.toLatin1()))
    {
        return 1;
    }
    // 判断是否包含"250"开头的成功状态
    if (buffer.startsWith("250")) {
        return 1;
    }

    // 或者使用正则表达式进行更严格匹配
    QRegExp exp("^250.*OK");
    if (exp.exactMatch(buffer)) {
        return 1;
    }

    // 如果需要匹配多个状态码，可以使用 contains
    if (buffer.contains("250") || buffer.contains("220")) {
        return 1;
    }
    return 0;
}

void PasswordSmtp::CheckConnectState()//确认与服务器的连接，随后发送helo sis
{
    sslSocket->waitForReadyRead(5000);
    QString buffer = sslSocket->readAll();
    if(sslSocket->state() == QAbstractSocket::ConnectedState)
    {
        SendHeloSis();
    }
    else
    {
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("当前无法连接至邮件服务，请修复后重试"),QMessageBox::Yes);
    }
}

void PasswordSmtp::SendHeloSis()//发送helo sis，以得到host回复，确认相关状态
{
    QString str = "ehlo localhost\r\n";
    qDebug()<<"Smtp::SendHeloSis  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK\r\n";
    if(ReadFromHost())//判断从服务器接受的是否符合预期
    {
        SendAuthLogin();
    }
}

void PasswordSmtp::SendAuthLogin()
//客户端发送 AUTH LOGIN 命令给服务器，以进行身份验证。
//使用基于用户名和密码的身份验证机制
{
    QString str = "auth login\r\n";
    qDebug()<<"Smtp::SendAuthLogin  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "334 VXNlcm5hbWU6\r\n";
    if(ReadFromHost())
    {
        SendMyEmailAddress();
    }
}

void PasswordSmtp::SendMyEmailAddress()//用户名，即邮箱地址
{
    QString str = QString("\r\n").prepend(QString("2466863352@qq.com").toLatin1().toBase64());//自己邮箱
    qDebug()<<"Smtp::SendMyEmailAddress  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "334 UGFzc3dvcmQ6\r\n";
    if(ReadFromHost())
    {
        SendAuthCode();
    }
}

void PasswordSmtp::SendAuthCode()  //发送授权码
{
    QString str = QString("\r\n").prepend(QString("qfsatqtvxedfdhji").toLatin1().toBase64());//自己授权码
    qDebug()<<"Smtp::SendAuthCode  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());//通过write()方法发送数据
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "235 Authentication successful\r\n";
    if(ReadFromHost())
    {
        SendEmailFrom();
    }
}

void PasswordSmtp::SendEmailFrom()//发送方
{
    QString str = QString("mail from:<%1>\r\n").arg("2466863352@qq.com");
    qDebug()<<"Smtp::SendEmailFrom  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK";
    if(ReadFromHost())
    {
        SendRcptTo();
    }
}

void PasswordSmtp::SendRcptTo()//接收方
{
    QString str = QString("rcpt to:<%1>\r\n").arg(ReceiverEmailAddress);
    qDebug()<<"Smtp::SendRcptTo  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK\r\n";
    if(ReadFromHost())
    {
        StartSendContent();
    }
}

void PasswordSmtp::StartSendContent()//发送data，表示准备开始发送邮件正文
{
    QString str = "data\r\n";
    qDebug()<<"Smtp::StartSendContent  向服务器发送了:"<<str;
    sslSocket->write(str.toLatin1());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "354 End data with <CR><LF>.<CR><LF>";
    if(ReadFromHost())
    {
        SendContent();
    }
}

void PasswordSmtp::SendContent()
{
    QString Time_Now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString senderMail = "2466863352@qq.com";
    QString title = "投票系统密码信息";
    QString content = "亲爱的用户:\r\n欢迎您使用投票系统，您的密码为"+ Password +",请勿将密码泄露给其他人，若您未注册系统，请忽略此邮件。\r\n\r\n本邮件于"+Time_Now+"自动生成，请勿回复。";
    QString str = QString("subject:投票系统密码找回\r\n"
                          "FROM:%1 <2466863352@qq.com>\r\n"
                          "TO:%2\r\n"
                          "\r\n"
                          "%3\r\n"
                          "\r\n"
                          ".\r\n").arg("投票系统").arg(ReceiverEmailAddress).arg(content);
    qDebug()<<"向服务器发送：　" + str;//这里在from时，要符合qq格式from:nickname <邮箱>
    sslSocket->write(str.toUtf8());
    sslSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK: queued as";
    if(ReadFromHost())
    {
        SendingStateConfirm();
        QMessageBox::information(nullptr, "提示","密码信息已发送，请及时查收");
    }
}

void PasswordSmtp::SendingStateConfirm()
{
    QString str = "quit\r\n";
    sslSocket->write(str.toUtf8());
    sslSocket->waitForBytesWritten(5000);
    //221 Bye
}
void PasswordSmtp::SetValue(QString value)
{
    Password = value;
}
