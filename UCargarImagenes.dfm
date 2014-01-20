object frmCargarImagenes: TfrmCargarImagenes
  Left = 437
  Top = 174
  Width = 171
  Height = 356
  BorderIcons = []
  Caption = 'Load images'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblDirectory: TLabel
    Left = 8
    Top = 8
    Width = 79
    Height = 13
    Caption = 'Select directory :'
  end
  object Label1: TLabel
    Left = 8
    Top = 248
    Width = 25
    Height = 13
    Caption = 'Drive'
  end
  object dlbDirectory: TDirectoryListBox
    Left = 8
    Top = 32
    Width = 145
    Height = 209
    FileList = flbFiles
    ItemHeight = 16
    TabOrder = 0
  end
  object dcbDrive: TDriveComboBox
    Left = 8
    Top = 264
    Width = 145
    Height = 19
    DirList = dlbDirectory
    TabOrder = 1
  end
  object butApply: TButton
    Left = 4
    Top = 296
    Width = 75
    Height = 25
    Caption = 'Apply'
    ModalResult = 1
    TabOrder = 2
    OnClick = butApplyClick
  end
  object butCancel: TButton
    Left = 84
    Top = 296
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
  object flbFiles: TFileListBox
    Left = 24
    Top = 112
    Width = 97
    Height = 97
    ItemHeight = 13
    Mask = '*.bmp'
    TabOrder = 4
    Visible = False
  end
  object FilterComboBox1: TFilterComboBox
    Left = 24
    Top = 216
    Width = 97
    Height = 21
    FileList = flbFiles
    Filter = 'bitmap file|*.bmp'
    TabOrder = 5
    Visible = False
  end
end
