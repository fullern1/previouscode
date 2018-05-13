# w1wx.py
import wx
import sys
         
def OnClickCallback(event):
  print "clicked"
  frame.Destroy()
  sys.exit()

app = wx.PySimpleApp()
frame = wx.Frame(None, title="w1wx.py")
click = wx.Button(frame, -1,  "Click here to Exit!")
click.Bind(wx.EVT_BUTTON, OnClickCallback)

frame.Show()
app.MainLoop()

