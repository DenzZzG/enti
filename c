wait(0.5)

-- Create GUI elements
local gui = Instance.new("ScreenGui")
local mainFrame = Instance.new("Frame")
local titleLabel = Instance.new("TextLabel")
local statusLabel = Instance.new("TextLabel")
local closeButton = Instance.new("TextButton")

-- Set parent to CoreGui
gui.Parent = game.CoreGui

-- Main Frame
mainFrame.Parent = gui
mainFrame.BackgroundColor3 = Color3.new(0.2, 0.2, 0.2)
mainFrame.Position = UDim2.new(0.7, 0, 0.1, 0)
mainFrame.Size = UDim2.new(0, 200, 0, 60)
mainFrame.Active = true

-- Title Label
titleLabel.Parent = mainFrame
titleLabel.BackgroundColor3 = Color3.new(0.3, 0.3, 0.3)
titleLabel.Size = UDim2.new(0.8, 0, 0.5, 0)
titleLabel.Position = UDim2.new(0, 0, 0, 0)
titleLabel.Font = Enum.Font.SourceSansSemibold
titleLabel.Text = "AntiAFKScript"
titleLabel.TextColor3 = Color3.new(0, 1, 1)
titleLabel.TextSize = 18
titleLabel.TextScaled = true
titleLabel.TextWrapped = true
titleLabel.TextXAlignment = Enum.TextXAlignment.Center

-- Status Label
statusLabel.Parent = mainFrame
statusLabel.BackgroundColor3 = Color3.new(0.2, 0.2, 0.2)
statusLabel.Position = UDim2.new(0, 0, 0.5, 0)
statusLabel.Size = UDim2.new(1, 0, 0.5, 0)
statusLabel.Font = Enum.Font.Arial
statusLabel.Text = "AntiAFK: ON"
statusLabel.TextColor3 = Color3.new(0.2, 0.8, 0.2)
statusLabel.TextSize = 18
statusLabel.TextScaled = true
statusLabel.TextWrapped = true
statusLabel.TextXAlignment = Enum.TextXAlignment.Center

-- Close Button
closeButton.Parent = mainFrame
closeButton.BackgroundColor3 = Color3.new(0.8, 0.2, 0.2)
closeButton.Position = UDim2.new(0.8, 0, 0, 0)
closeButton.Size = UDim2.new(0.2, 0, 0.5, 0)
closeButton.Font = Enum.Font.SourceSans
closeButton.Text = "X"
closeButton.TextColor3 = Color3.new(1, 1, 1)
closeButton.TextSize = 18
closeButton.TextScaled = true
closeButton.TextWrapped = true
closeButton.MouseButton1Click:Connect(function()
    gui:Destroy()
end)

-- Dragging functionality
local dragging
local dragInput
local dragStart
local startPos

mainFrame.InputBegan:Connect(function(input)
    if input.UserInputType == Enum.UserInputType.MouseButton1 then
        dragging = true
        dragStart = input.Position
        startPos = mainFrame.Position

        input.Changed:Connect(function()
            if input.UserInputState == Enum.UserInputState.End then
                dragging = false
            end
        end)
    end
end)

mainFrame.InputChanged:Connect(function(input)
    if input.UserInputType == Enum.UserInputType.MouseMovement or input.UserInputType == Enum.UserInputType.Touch then
        dragInput = input
    end
end)

game:GetService("UserInputService").InputChanged:Connect(function(input)
    if dragging and input == dragInput then
        local delta = input.Position - dragStart
        mainFrame.Position = UDim2.new(startPos.X.Scale, startPos.X.Offset + delta.X, startPos.Y.Scale, startPos.Y.Offset + delta.Y)
    end
end)

-- Anti-AFK Script
local virtualUser = game:service'VirtualUser'

game:service'Players'.LocalPlayer.Idled:Connect(function()
    virtualUser:CaptureController()
    virtualUser:ClickButton2(Vector2.new())
end)
