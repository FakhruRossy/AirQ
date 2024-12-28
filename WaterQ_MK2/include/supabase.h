#ifndef SUPABASE_H
#define SUPABASE_H

class SupabaseDB
{
private:
    const public : SupabaseDB();
    ~SupabaseDB();
    void connect();
    void disconnect();
    bool isConnected();
    String send(JsonDocument doc);
};

#endif