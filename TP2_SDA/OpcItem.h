class OpcItem {
public:
    std::wstring itemID;
    VARIANT value;
    FILETIME timestamp;
    WORD quality;

    OPCItem(const std::wstring& id);
    void read();
    void write(const VARIANT& val);
};