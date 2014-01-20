object frmRange: TfrmRange
  Left = 270
  Top = 88
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Selected plant colors'
  ClientHeight = 316
  ClientWidth = 196
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 8
    Width = 24
    Height = 13
    Caption = 'Red'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 72
    Top = 8
    Width = 35
    Height = 13
    Caption = 'Green'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 120
    Top = 8
    Width = 26
    Height = 13
    Caption = 'Blue'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 16
    Top = 240
    Width = 58
    Height = 13
    Caption = 'Tolerance'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lbPixel: TListBox
    Left = 24
    Top = 24
    Width = 153
    Height = 169
    ItemHeight = 13
    TabOrder = 0
    OnClick = lbPixelClick
  end
  object Button1: TButton
    Left = 23
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Remove'
    TabOrder = 1
    OnClick = Button1Click
  end
  object tbTolerance: TTrackBar
    Left = 24
    Top = 256
    Width = 150
    Height = 45
    Max = 100
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 2
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = tbToleranceChange
  end
  object Edit1: TEdit
    Left = 76
    Top = 288
    Width = 49
    Height = 21
    Enabled = False
    TabOrder = 3
    Text = '0'
    OnChange = Edit1Change
  end
  object Button2: TButton
    Left = 104
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Clear all'
    TabOrder = 4
    OnClick = Button2Click
  end
end
