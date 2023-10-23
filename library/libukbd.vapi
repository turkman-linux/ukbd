[CCode (cheader_filename = "libukbd.h")]
namespace libukbd {

    [CCode (cname = "ukbd_event")]
    public void event (int code, int status);

    [CCode (cname = "ukbd_press")]
    public void press (int code);

    [CCode (cname = "ukbd_release")]
    public void release (int code);

    [CCode (cname = "ukbd_send")]
    public void send (int code);
}
