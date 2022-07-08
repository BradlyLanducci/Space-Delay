/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessor.cpp"

//==============================================================================
DelayLineAudioProcessorEditor::DelayLineAudioProcessorEditor 
(DelayLineAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red);
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    feedbackLabel.setText("feedback", juce::NotificationType::dontSendNotification);
    feedbackSlider.setRotaryParameters(4.712385f, 7.853975f, true);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "feedback", feedbackSlider);

    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(feedbackLabel);

    lengthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lengthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    lengthSlider.setRange(0.0f, 1.0f, 0.25f);
    lengthSlider.setRotaryParameters(4.712385f, 7.853975f, true);
    lengthLabel.setText("length", juce::NotificationType::dontSendNotification);
    lengthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "length", lengthSlider);

    addAndMakeVisible(lengthSlider);
    addAndMakeVisible(lengthLabel);

    delayType.addItem("Earth", 1);
    delayType.addItem("Mars", 2);
    delayType.setSelectedId(0, juce::NotificationType::dontSendNotification);
    delayType.setText(delayType.getItemText(delayType.getSelectedId()));

    addAndMakeVisible(delayType);

    setSize(500, 500);
}

DelayLineAudioProcessorEditor::~DelayLineAudioProcessorEditor()
{
}

//==============================================================================
void DelayLineAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB(0, 0, 0));

    g.setColour (juce::Colours::white);
    g.setFont (75.0f);
    g.drawText("Space Delay", getLocalBounds(), juce::Justification::centredTop);
}

void DelayLineAudioProcessorEditor::resized()
{
    feedbackSlider.setBounds({ 200, 35, 100, 300 });
    feedbackLabel.setBounds({ feedbackSlider.getX() + (feedbackSlider.getWidth() / 4),
                                210,
                                200, 50 });
    lengthSlider.setBounds({ 200, 200, 100, 300 });
    lengthLabel.setBounds({ lengthSlider.getX() + (lengthSlider.getWidth() / 4), 375,
                                200, 50 });
    delayType.setBounds({ 200, 425, 100, 25 });
}

void DelayLineAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &lengthSlider)
    {
        dl.clear();
    }
}